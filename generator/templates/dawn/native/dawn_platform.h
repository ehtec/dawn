//* Copyright 2021 The Dawn & Tint Authors
//*
//* Redistribution and use in source and binary forms, with or without
//* modification, are permitted provided that the following conditions are met:
//*
//* 1. Redistributions of source code must retain the above copyright notice, this
//*    list of conditions and the following disclaimer.
//*
//* 2. Redistributions in binary form must reproduce the above copyright notice,
//*    this list of conditions and the following disclaimer in the documentation
//*    and/or other materials provided with the distribution.
//*
//* 3. Neither the name of the copyright holder nor the names of its
//*    contributors may be used to endorse or promote products derived from
//*    this software without specific prior written permission.
//*
//* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

{% set namespace_name = Name(metadata.native_namespace) %}
{% set NATIVE_DIR = namespace_name.concatcase().upper() %}
{% set PREFIX = metadata.proc_table_prefix.upper() %}
#ifndef {{NATIVE_DIR}}_{{PREFIX}}_PLATFORM_AUTOGEN_H_
#define {{NATIVE_DIR}}_{{PREFIX}}_PLATFORM_AUTOGEN_H_

{% set api = metadata.api.lower() %}
#include "dawn/{{api}}_cpp.h"
{% set impl_dir = metadata.impl_dir + "/" if metadata.impl_dir else "" %}
{% set native_namespace = namespace_name.namespace_case() %}
{% set native_dir = impl_dir + namespace_name.Dirs() %}
#include "{{native_dir}}/Forward.h"

{% set namespace = metadata.namespace %}
// Use our autogenerated version of the {{namespace}} structures that point to {{native_namespace}} object types
// (wgpu::Buffer is dawn::native::BufferBase*)
#include <{{native_dir}}/{{namespace}}_structs_autogen.h>

{% macro render_structure_conversions(name) -%}
    inline const {{as_cType(name)}}* ToAPI(const {{as_cppType(name)}}* rhs) {
        return reinterpret_cast<const {{as_cType(name)}}*>(rhs);
    }
    inline {{as_cType(name)}}* ToAPI({{as_cppType(name)}}* rhs) {
        return reinterpret_cast<{{as_cType(name)}}*>(rhs);
    }
    inline const {{as_cppType(name)}}* FromAPI(const {{as_cType(name)}}* rhs) {
        return reinterpret_cast<const {{as_cppType(name)}}*>(rhs);
    }
    inline {{as_cppType(name)}}* FromAPI({{as_cType(name)}}* rhs) {
        return reinterpret_cast<{{as_cppType(name)}}*>(rhs);
    }
    inline const {{metadata.namespace}}::{{as_cppType(name)}}* ToCppAPI(const {{as_cppType(name)}}* rhs) {
        return reinterpret_cast<const {{metadata.namespace}}::{{as_cppType(name)}}*>(rhs);
    }
    inline {{metadata.namespace}}::{{as_cppType(name)}}* ToCppAPI({{as_cppType(name)}}* rhs) {
        return reinterpret_cast<{{metadata.namespace}}::{{as_cppType(name)}}*>(rhs);
    }
    inline const {{as_cppType(name)}}* FromCppAPI(const {{metadata.namespace}}::{{as_cppType(name)}}* rhs) {
        return reinterpret_cast<const {{as_cppType(name)}}*>(rhs);
    }
    inline {{as_cppType(name)}}* FromCppAPI({{metadata.namespace}}::{{as_cppType(name)}}* rhs) {
        return reinterpret_cast<{{as_cppType(name)}}*>(rhs);
    }
{%- endmacro %}

namespace {{native_namespace}} {

    {% set ChainedStructName = Name("chained struct") %}
    {{render_structure_conversions(ChainedStructName)|indent}}

    {% for type in by_category["structure"] if type.name.get() != "string view" %}
        {{render_structure_conversions(type.name)|indent}}

    {% endfor %}

    {% for type in by_category["object"] %}
        inline const {{as_cType(type.name)}}Impl* ToAPI(const {{as_cppType(type.name)}}Base* rhs) {
            return reinterpret_cast<const {{as_cType(type.name)}}Impl*>(rhs);
        }

        inline {{as_cType(type.name)}}Impl* ToAPI({{as_cppType(type.name)}}Base* rhs) {
            return reinterpret_cast<{{as_cType(type.name)}}Impl*>(rhs);
        }

        inline const {{as_cppType(type.name)}}Base* FromAPI(const {{as_cType(type.name)}}Impl* rhs) {
            return reinterpret_cast<const {{as_cppType(type.name)}}Base*>(rhs);
        }

        inline {{as_cppType(type.name)}}Base* FromAPI({{as_cType(type.name)}}Impl* rhs) {
            return reinterpret_cast<{{as_cppType(type.name)}}Base*>(rhs);
        }
    {% endfor %}

    template <typename T>
    struct EnumCount;

    {% for e in by_category["enum"] if e.contiguous and e.startValue == 0 %}
        template<>
        struct EnumCount<{{namespace}}::{{as_cppType(e.name)}}> {
            static constexpr uint32_t value = {{len(e.values)}};
        };
    {% endfor %}

    {% for type in by_category["enum"] + by_category["bitmask"] %}
        inline {{as_cType(type.name)}} ToAPI({{namespace}}::{{as_cppType(type.name)}} rhs) {
            return static_cast<{{as_cType(type.name)}}>(rhs);
        }
    {% endfor %}

    {% for type in by_category["enum"] %}
        inline {{namespace}}::{{as_cppType(type.name)}} FromAPI({{as_cType(type.name)}} rhs) {
            return static_cast<{{namespace}}::{{as_cppType(type.name)}}>(rhs);
        }
    {% endfor %}
}  // namespace {{native_namespace}}

#endif  // {{NATIVE_DIR}}_{{PREFIX}}_PLATFORM_AUTOGEN_H_
