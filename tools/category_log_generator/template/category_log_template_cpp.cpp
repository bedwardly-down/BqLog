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
#include <inttypes.h>
#include <stdio.h>
#include "template/category_log_template_cpp.h"

namespace bq {
    bq::string category_log_template_cpp::format(const bq::string& template_string, const category_node& root_node) const
    {
        bq::string generated_code = template_string;
        generated_code = replace_with_tab_format(generated_code, "${CLASS_NAME}", class_name_);
        generated_code = replace_with_tab_format(generated_code, "${CATEGORY_NAMES}", get_category_names_code(root_node));
        generated_code = replace_with_tab_format(generated_code, "${CATEGORY_ROOT_CLASS}", get_category_class_root_define_code(root_node));
        generated_code = replace_with_tab_format(generated_code, "${CATEGORIES_COUNT}", uint64_to_string((uint64_t)root_node.get_all_nodes_count()));

        return generated_code;
    }

    bq::string category_log_template_cpp::get_category_names_code_recursive(const category_node& node) const
    {
        bq::string tab = "            ";
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

    bq::string category_log_template_cpp::get_category_class_code_recursive(const category_node& node, const bq::string& tab, uint64_t& index) const
    {
        bq::string code;
        // empty means it is root node, default category, needn't generate category.
        if (!node.name().is_empty()) {
            code += tab;
            code += "struct EBCO : public ";
            code += class_name_;
            code += "_category_base<";
            code += uint64_to_string(index);
            code += "> {\n";
        }
        ++index;
        for (const auto& child : node.get_all_children()) {
            code += get_category_class_code_recursive(*child, tab + "    ", index);
        }
        if (!node.name().is_empty()) {
            code += tab;
            code += "} ";
            code += node.name();
            code += ";    //";
            code += node.full_name();
            if (!node.comment().trim().is_empty()) {
                code += "    //" + node.comment();
            }
            code += "\n";
        }
        return code;
    }

    bq::string category_log_template_cpp::get_category_names_code(const category_node& root_node) const
    {
        size_t total_categories_count = root_node.get_all_nodes_count();
        bq::string code = "const char* names[" + uint64_to_string((uint64_t)total_categories_count) + "] = {\n";
        code += get_category_names_code_recursive(root_node);
        code += "};";
        return code;
    }

    bq::string category_log_template_cpp::get_category_class_root_define_code(const category_node& root_node) const
    {
        bq::string code = "struct EBCO ";
        code += class_name_;
        code += "_category_root\n";
        code += "{\n";
        uint64_t index = 0;
        code += get_category_class_code_recursive(root_node, "", index);
        code += "};";
        return code;
    }

    bq::string category_log_template_cpp::get_template_content() const
    {
        return
            R"(#pragma once
// clang-format off
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
/*!
 * Generated Wrapper For ${CLASS_NAME}
 *
 * This is a category_log that supports attaching a category to each log entry.
 * Categories can be used to filter logs within the appender settings.
 *
 *  Usage: 
 *  bq::${CLASS_NAME} my_category_log = bq::${CLASS_NAME}::create_log(log_name, log_config);  //create a ${CLASS_NAME} object with config.
 *  my_category_log.info("content");  //this is for empty category
 *  my_category_log.info(my_category_log.cat.moduleA.classB, "content"); //this is a log entry for category ModuleA.ClassB. it is generated by your Category Config File
 */

#include "bq_log/bq_log.h"


namespace bq {
    class ${CLASS_NAME} : public category_log
    {
    private:
        template<uint32_t CAT_INDEX>
        struct ${CLASS_NAME}_category_base : public bq::log_category_base<CAT_INDEX> {};

        struct ${CLASS_NAME}_category_config
        {
            ${CATEGORY_NAMES}
        };

        ${CATEGORY_ROOT_CLASS}

        template<typename T>
        struct ${CLASS_NAME}_category_root_holder
        {
            static ${CLASS_NAME}_category_config config_;
            static ${CLASS_NAME}_category_root root_;
        };

    public:
        const ${CLASS_NAME}_category_root& cat = ${CLASS_NAME}_category_root_holder<void>::root_;

    protected:
        template<typename STR>
        struct is_${CLASS_NAME}_format_type
        {
            static constexpr bool value = bq::tools::_is_bq_log_format_type<STR>::value;
        };

    private:
        ${CLASS_NAME}() : category_log(){}
        ${CLASS_NAME}(const log& child_inst) : category_log(child_inst){}

    public:
        /// <summary>
        /// Create a ${CLASS_NAME} object
        /// </summary>
        /// <param name="log_name">If the log name is an empty string, bqLog will automatically assign you a unique log name. If the log name already exists, it will return the previously existing log object and overwrite the previous configuration with the new config.</param>
        /// <param name="config_content">Log config string</param>
        /// <returns>A ${CLASS_NAME} object, if create failed, the is_valid() method of it will return false</returns>
        static ${CLASS_NAME} create_log(const bq::string& log_name, const bq::string& config_content);

        /// <summary>
        /// Get a ${CLASS_NAME} object by it's name
        /// </summary>
        /// <param name="log_name">Name of the ${CLASS_NAME} object you want to find</param>
        /// <returns>A ${CLASS_NAME} object, if the ${CLASS_NAME} object with specific name was not found, the is_valid() method of it will return false</returns>
        static ${CLASS_NAME} get_log_by_name(const bq::string& log_name);

        using log::verbose;
        using log::debug;
        using log::info;
        using log::warning;
        using log::error;
        using log::fatal;

        ///Core log functions with category param, there are 6 log levels:
        ///verbose, debug, info, warning, error, fatal
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> verbose(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> verbose(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> debug(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> debug(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> info(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> info(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> warning(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> warning(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> error(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> error(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
        template<typename STR, uint32_t CAT_INDEX>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> fatal(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const;
        template<typename STR, uint32_t CAT_INDEX, typename...Args>
        bq::enable_if_t<is_${CLASS_NAME}_format_type<STR>::value, bool> fatal(const ${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const;
    };

    template<typename T>
    ${CLASS_NAME}::${CLASS_NAME}_category_root ${CLASS_NAME}::${CLASS_NAME}_category_root_holder<T>::root_;
    template<typename T>
    ${CLASS_NAME}::${CLASS_NAME}_category_config ${CLASS_NAME}::${CLASS_NAME}_category_root_holder<T>::config_;

    inline ${CLASS_NAME} ${CLASS_NAME}::create_log(const bq::string& log_name, const bq::string& config_content)
    {
        uint64_t log_id = api::__api_create_log(log_name.c_str(), config_content.c_str(), ${CATEGORIES_COUNT}, ${CLASS_NAME}_category_root_holder<void>::config_.names);
        log result = get_log_by_id(log_id);
        return result;
    }
    
    inline ${CLASS_NAME} ${CLASS_NAME}::get_log_by_name(const bq::string& log_name)
    {
        ${CLASS_NAME} result = log::get_log_by_name(log_name);
        if (!result.is_valid())
        {
            return result;
        }
        //check categories
        if (result.get_categories_count() != ${CATEGORIES_COUNT})
        {
            return ${CLASS_NAME}();
        }
        for (size_t i = 0; i < result.get_categories_count(); ++i)
        {
            if (result.get_categories_name_array()[i] != ${CLASS_NAME}_category_root_holder<void>::config_.names[i])
            {
                return ${CLASS_NAME}();
            }
        }
        return result;
    }

    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::verbose(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::verbose, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::verbose(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::verbose, log_format_content, args...);
    }
    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::debug(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::debug, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::debug(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::debug, log_format_content, args...);
    }
    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::info(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::info, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::info(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::info, log_format_content, args...);
    }
    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::warning(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::warning, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::warning(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::warning, log_format_content, args...);
    }
    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::error(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::error, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::error(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::error, log_format_content, args...);
    }
    template<typename STR, uint32_t CAT_INDEX>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::fatal(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_content) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::fatal, log_content);
    }
    template<typename STR, uint32_t CAT_INDEX, typename...Args>
    inline bq::enable_if_t<${CLASS_NAME}::is_${CLASS_NAME}_format_type<STR>::value, bool> ${CLASS_NAME}::fatal(const ${CLASS_NAME}::${CLASS_NAME}_category_base<CAT_INDEX>& cat, const STR& log_format_content, const Args&... args) const
    {
        (void)cat;
        return do_log(CAT_INDEX, log_level::fatal, log_format_content, args...);
    }
}
// clang-format on
        )";
    }
}
