﻿/*
 * Copyright (C) 2024 THL A29 Limited, a Tencent company.
 * BQLOG is licensed under the Apache License, Version 2.0.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
#include "template/category_log_template_java.h"

namespace bq {

    bq::string category_log_template_java::format(const bq::string& template_string, const category_node& root_node) const
    {
        bq::string generated_code = template_string;
        generated_code = replace_with_tab_format(generated_code, "${CLASS_NAME}", class_name_);
        generated_code = replace_with_tab_format(generated_code, "${CATEGORY_NAMES}", get_category_names_code(root_node));
        generated_code = replace_with_tab_format(generated_code, "${CATEGORY_ROOT_CLASS}", get_category_class_root_define_code(root_node));

        return generated_code;
    }

    bq::string category_log_template_java::get_category_names_code_recursive(const category_node& node) const
    {
        bq::string tab = "    ";
        bq::string code = tab;
        if (node.parent()) // empty means it is root node, first value
        {
            code += ", ";
        }
        code += "\"" + node.full_name() + "\"\n";
        for (const auto& child : node.get_all_children()) {
            code += get_category_names_code_recursive(*child);
        }
        return code;
    }
    bq::string category_log_template_java::get_category_class_code_recursive(const category_node& node, const bq::string& tab, uint64_t& index) const
    {
        bq::string node_class_name = class_name_ + "_" + node.name();
        bq::string code = tab + "public static class " + node_class_name + " extends " + class_name_ + "_category_base\n";
        code += tab + "{\n";
        ++index;
        code += tab + "    public " + node_class_name + "(){index = " + uint64_to_string(index) + "L;}\n";

        for (const auto& child : node.get_all_children()) {
            code += get_category_class_code_recursive(*child, tab + "    ", index);
        }
        code += tab + "}\n";
        code += tab + "public " + node_class_name + " " + node.name() + " = new " + node_class_name + "();     //" + node.full_name();
        if (!node.comment().trim().is_empty()) {
            code += "    //" + node.comment();
        }
        code += "\n";
        return code;
    }

    bq::string category_log_template_java::get_category_names_code(const category_node& root_node) const
    {
        bq::string code = "{\n";
        code += get_category_names_code_recursive(root_node);
        code += "}";
        return code;
    }

    bq::string category_log_template_java::get_category_class_root_define_code(const category_node& root_node) const
    {
        bq::string code = "public static class " + class_name_ + "_category_root\n";
        code += "{\n";
        uint64_t index = 0;
        for (const auto& child : root_node.get_all_children()) {
            code += get_category_class_code_recursive(*child, "    ", index);
        }
        code += "}\n";
        return code;
    }

    bq::string category_log_template_java::get_template_content() const
    {
        return R"(package bq;
/*
 * Copyright (C) 2024 THL A29 Limited, a Tencent company.
 * BQLOG is licensed under the Apache License, Version 2.0.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

import bq.def.*;
import bq.impl.log_invoker;

/*!
 * Generated Wrapper For ${CLASS_NAME}
 *
 * This is a category_log that supports attaching a category to each log entry.
 * Categories can be used to filter logs within the appender settings.
 *
 *    Usage: 
 *    bq.${CLASS_NAME} my_category_log = bq.${CLASS_NAME}::create_log(log_name, log_config);  //create a ${CLASS_NAME} object with config.
 *    my_category_log.info("content");  //this is for empty category
 *  my_category_log.info(my_category_log.cat.moduleA.classB, "content"); //this is a log entry for category ModuleA.ClassB, which was generated by your Category Config File
 */

public class ${CLASS_NAME} extends category_log{
    private ${CLASS_NAME}()
    {
        super();
    }
    
    private ${CLASS_NAME}(log child_inst)
    {
        super(child_inst);
    }
    
    /**
     * Create a ${CLASS_NAME} object
     * @param name 
     *             If the ${CLASS_NAME} name is an empty string, bqLog will automatically assign you a unique name. 
     *             If the ${CLASS_NAME} name already exists, it will return the previously existing ${CLASS_NAME} object and overwrite the previous configuration with the new config.
     * @param config
     *             ${CLASS_NAME} config string
     * @return
     *             A ${CLASS_NAME} object, if create failed, the is_valid() method of it will return false
     */
    public static ${CLASS_NAME} create_log(String name, String config)
    {
        if (config == null || config.length() == 0)
        {
            return new ${CLASS_NAME}();
        }
        long log_handle = log_invoker.__api_create_log(name, config, ${CLASS_NAME}.categories_count, ${CLASS_NAME}.category_names);
        log result = get_log_by_id(log_handle);
        return new ${CLASS_NAME}(result);
    }
    
    /**
     * Get a ${CLASS_NAME} object by it's name
     * @param log_name
     *             Name of the ${CLASS_NAME} you want to find
     * @return
     *             A ${CLASS_NAME} object, if the ${CLASS_NAME} object with specific name was not found, the is_valid() method of it will return false
     */
    public static ${CLASS_NAME} get_log_by_name(String log_name)
    {
        ${CLASS_NAME} result = new ${CLASS_NAME}(log.get_log_by_name(log_name));
        if(!result.is_valid())
        {
            return result;
        }
        //check categories
        if (result.get_categories_count() != ${CLASS_NAME}.categories_count)
        {
            return new ${CLASS_NAME}();
        }
        for (long i = 0; i < result.get_categories_count(); ++i)
        {
            if (!${CLASS_NAME}.category_names[(int)i].equals(result.get_categories_name_array().get((int)i)))
            {
                return new ${CLASS_NAME}();
            }
        }
        return result;
    }
    

    ///Core log functions with category param, there are 6 log levels:
    ///verbose, debug, info, warning, error, fatal
    public boolean verbose(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.verbose, log_format_content, args);
    }
    public boolean debug(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.debug, log_format_content, args);
    }
    public boolean info(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.info, log_format_content, args);
    }
    public boolean warning(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.warning, log_format_content, args);
    }
    public boolean error(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.error, log_format_content, args);
    }
    public boolean fatal(${CLASS_NAME}_category_base cat, String log_format_content, Object... args)
    {
        return do_log(cat, log_level.fatal, log_format_content, args);
    }
    
    
    
    
    /****************************************************************************************************************/
    /**                                 Code Generated By Categories                                              ***/
    /****************************************************************************************************************/
    private static final String[] category_names = ${CATEGORY_NAMES};
    private static final long categories_count = (long)category_names.length;
    private static class ${CLASS_NAME}_category_base extends log_category_base
    {
    }
    ${CATEGORY_ROOT_CLASS}
    
    public final ${CLASS_NAME}_category_root cat = new ${CLASS_NAME}_category_root();
}
)";
    }
}
