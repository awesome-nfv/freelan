/*
 * libkfather - C++ JSON parser/producer library.
 * Copyright (C) 2010-2012 Julien Kauffmann <julien.kauffmann@freelan.org>
 *
 * This file is part of libkfather.
 *
 * libkfather is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libkfather is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * If you intend to use libkfather in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file parser.hpp
 * \author Julien Kauffmann <julien.kauffmann@freelan.org>
 * \brief A JSON parser class.
 */

#ifndef KFATHER_PARSER_HPP
#define KFATHER_PARSER_HPP

#include <iostream>

#include <boost/function.hpp>

#include <iconvplus/iconv_instance.hpp>

#include "value.hpp"

namespace kfather
{
	/**
	 * \brief A JSON parser class.
	 *
	 * parser objects are thread-safe and reentrant in the sense that the same
	 * parser instance can be used to parse different strings (or even the same
	 * string) at the same time.
	 *
	 * Note however that modifying a parser instance while parsing has undefined
	 * behavior.
	 *
	 * A parser can be used to validate JSON input, to transform (normalize,
	 * format) JSON input or to build a JSON value tree.
	 */
	class parser
	{
		public:

			/**
			 * \brief A JSON object callback type.
			 */
			typedef boost::function<void ()> object_callback;

			/**
			 * \brief A JSON array callback type.
			 */
			typedef boost::function<void ()> array_callback;

			/**
			 * \brief A JSON string callback type.
			 */
			typedef boost::function<void (const string_type&)> string_callback;

			/**
			 * \brief A JSON number callback type.
			 */
			typedef boost::function<void (const number_type&)> number_callback;

			/**
			 * \brief A JSON boolean callback type.
			 */
			typedef boost::function<void (const boolean_type&)> boolean_callback;

			/**
			 * \brief A JSON null callback type.
			 */
			typedef boost::function<void (const null_type&)> null_callback;

			/**
			 * \brief A JSON object start callback type.
			 */
			typedef boost::function<void ()> object_start_callback;

			/**
			 * \brief A JSON object colon callback type.
			 */
			typedef boost::function<void ()> object_colon_callback;

			/**
			 * \brief A JSON object comma callback type.
			 */
			typedef boost::function<void ()> object_comma_callback;

			/**
			 * \brief A JSON object stop callback type.
			 */
			typedef boost::function<void ()> object_stop_callback;

			/**
			 * \brief A JSON array start callback type.
			 */
			typedef boost::function<void ()> array_start_callback;

			/**
			 * \brief A JSON array comma callback type.
			 */
			typedef boost::function<void ()> array_comma_callback;

			/**
			 * \brief A JSON array stop callback type.
			 */
			typedef boost::function<void ()> array_stop_callback;

			/**
			 * \brief Create a new parser.
			 */
			parser();

			/**
			 * \brief Parse the specified JSON string buffer.
			 * \param buf The buffer to parse. Must contain a valid JSON string or
			 * the call will fail. The string must be UTF-8 encoded. buf cannot be
			 * null.
			 * \param buflen The length of buf.
			 * \param error_token A pointer to a pointer to the first invalid
			 * character of buf, in case the parsing fails.
			 * \return true if the parsing succeeds, false otherwise.
			 *
			 * If the parsing fails, and error_token is not null, *error_token is set
			 * to the first invalid character in buf. That is, the position of the
			 * first invalid character of buf can be get by doing (error_token -
			 * buf).
			 *
			 * If the parsing succeeds, *error_token is guaranteed not to be
			 * modified.
			 */
			bool parse(const char* buf, size_t buflen, const char** error_token = NULL);

			/**
			 * \brief Parse the specified JSON string.
			 * \param str The JSON string to parse. Must contain a valid JSON string or
			 * the call will fail. The string must be UTF-8 encoded.
			 * \param error_pos A pointer to a position of the first invalid character.
			 * \return true if the parsing succeeds, false otherwise.
			 *
			 * If the parsing fails, and error_pos is not null, *error_pos is set
			 * to the position of the first invalid character in str.
			 *
			 * If the parsing succeeds, *error_pos is guaranteed not to be
			 * modified.
			 */
			bool parse(const std::string& str, std::string::size_type* error_pos = NULL);

			/**
			 * \brief Parse the specified input stream.
			 * \param is The input stream to parse. The stream must be UTF-8 encoded.
			 * \param error_pos A pointer to a position of the first invalid character.
			 * \return true if the parsing succeeds, false otherwise.
			 *
			 * If the parsing fails, and error_pos is not null, *error_pos is set
			 * to the position of the first invalid character in is.
			 *
			 * If the parsing succeeds, *error_pos is guaranteed not to be
			 * modified.
			 */
			bool parse(std::istream& is, size_t* error_pos = NULL);

			/**
			 * \brief Set or reset the object callback.
			 * \param cb The callback.
			 */
			void reset_object_callback(object_callback cb = object_callback())
			{
				m_object_callback = cb;
			}

			/**
			 * \brief Set or reset the array callback.
			 * \param cb The callback.
			 */
			void reset_array_callback(array_callback cb = array_callback())
			{
				m_array_callback = cb;
			}

			/**
			 * \brief Set or reset the string callback.
			 * \param cb The callback.
			 */
			void reset_string_callback(string_callback cb = string_callback())
			{
				m_string_callback = cb;
			}

			/**
			 * \brief Set or reset the number callback.
			 * \param cb The callback.
			 */
			void reset_number_callback(number_callback cb = number_callback())
			{
				m_number_callback = cb;
			}

			/**
			 * \brief Set or reset the true callback.
			 * \param cb The callback.
			 */
			void reset_boolean_callback(boolean_callback cb = boolean_callback())
			{
				m_boolean_callback = cb;
			}

			/**
			 * \brief Set or reset the null callback.
			 * \param cb The callback.
			 */
			void reset_null_callback(null_callback cb = null_callback())
			{
				m_null_callback = cb;
			}

			/**
			 * \brief Set or reset the object_start callback.
			 * \param cb The callback.
			 */
			void reset_object_start_callback(object_start_callback cb = object_start_callback())
			{
				m_object_start_callback = cb;
			}

			/**
			 * \brief Set or reset the object_colon callback.
			 * \param cb The callback.
			 */
			void reset_object_colon_callback(object_colon_callback cb = object_colon_callback())
			{
				m_object_colon_callback = cb;
			}

			/**
			 * \brief Set or reset the object_comma callback.
			 * \param cb The callback.
			 */
			void reset_object_comma_callback(object_comma_callback cb = object_comma_callback())
			{
				m_object_comma_callback = cb;
			}

			/**
			 * \brief Set or reset the object_stop callback.
			 * \param cb The callback.
			 */
			void reset_object_stop_callback(object_stop_callback cb = object_stop_callback())
			{
				m_object_stop_callback = cb;
			}

			/**
			 * \brief Set or reset the array_start callback.
			 * \param cb The callback.
			 */
			void reset_array_start_callback(array_start_callback cb = array_start_callback())
			{
				m_array_start_callback = cb;
			}

			/**
			 * \brief Set or reset the array_comma callback.
			 * \param cb The callback.
			 */
			void reset_array_comma_callback(array_comma_callback cb = array_comma_callback())
			{
				m_array_comma_callback = cb;
			}

			/**
			 * \brief Set or reset the array_stop callback.
			 * \param cb The callback.
			 */
			void reset_array_stop_callback(array_stop_callback cb = array_stop_callback())
			{
				m_array_stop_callback = cb;
			}

		private:

			/**
			 * \brief Parse a range of characters.
			 * \tparam IteratorType The iterator type.
			 * \param begin An iterator to the first character to parse.
			 * \param end An iterator past the last character to parse.
			 * \param error_pos A pointer to an iterator where the last parsing error occured.
			 * \return  true if the parsing succeeds, false otherwise.
			 *
			 * If the parsing fails, and error_pos is not null, *error_pos is set to
			 * the position of the first invalid character in [begin, end).
			 *
			 * If the parsing fails and error_pos == end, then the end of the range
			 * was reached before the parsing could be completed.
			 *
			 * If the parsing succeeds, *error_pos is guaranteed not to be
			 * modified.
			 */
			template <typename IteratorType>
			bool parse(IteratorType begin, IteratorType end, IteratorType* error_pos = NULL);

		private:

			class context
			{
				public:

					context();
					void clear();
					void push_char(char c);
					void push_codepoint(uint16_t cp);
					const std::string& str();
					bool get_number(number_type&);

				private:

					void end_codepoints();

					iconvplus::iconv_instance m_iconv;
					std::string m_utf16;
					string_type m_str;
			};

			template <typename IteratorType>
			bool parse_char(context& ctx, char c, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_value(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_object(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_array(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_string(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_number(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_true(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_false(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			bool parse_null(context& ctx, IteratorType& ch, IteratorType end);
			template <typename IteratorType>
			void skip_whitespace(context& ctx, IteratorType& ch, IteratorType end);

			object_callback m_object_callback;
			array_callback m_array_callback;
			string_callback m_string_callback;
			number_callback m_number_callback;
			boolean_callback m_boolean_callback;
			null_callback m_null_callback;

			object_start_callback m_object_start_callback;
			object_colon_callback m_object_colon_callback;
			object_comma_callback m_object_comma_callback;
			object_stop_callback m_object_stop_callback;
			array_start_callback m_array_start_callback;
			array_comma_callback m_array_comma_callback;
			array_stop_callback m_array_stop_callback;
	};
}

#endif /* KFATHER_PARSER_HPP */
