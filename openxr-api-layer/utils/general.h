// MIT License
//
// Copyright(c) 2022-2023 Matthieu Bucchianeri
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

namespace xr::math {

    static inline XrVector3f Cross(const XrVector3f& a, const XrVector3f& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
        };
    }

} // namespace xr::math

namespace openxr_api_layer::utils::general {

    struct ITimer {
        virtual ~ITimer() = default;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual uint64_t query() const = 0;
    };

    std::shared_ptr<ITimer> createTimer();

    static inline bool startsWith(const std::string& str, const std::string& substr) {
        return str.find(substr) == 0;
    }

    static inline bool endsWith(const std::string& str, const std::string& substr) {
        const auto pos = str.find(substr);
        return pos != std::string::npos && pos == str.size() - substr.size();
    }

    // Both ray and quadCenter poses must be located using the same base space.
    bool hitTest(const XrPosef& ray, const XrPosef& quadCenter, const XrExtent2Df& quadSize, XrPosef& hitPose);

    // Get UV coordinates for a point on quad.
    XrVector2f getUVCoordinates(const XrVector3f& point, const XrPosef& quadCenter, const XrExtent2Df& quadSize);
    static inline POINT getUVCoordinates(const XrVector3f& point,
                                         const XrPosef& quadCenter,
                                         const XrExtent2Df& quadSize,
                                         const XrExtent2Di& quadPixelSize) {
        const XrVector2f uv = getUVCoordinates(point, quadCenter, quadSize);
        return {static_cast<LONG>(uv.x * quadPixelSize.width), static_cast<LONG>(uv.y * quadPixelSize.height)};
    }

    std::optional<int> getSetting(const std::string& value);
    void setSetting(const std::string& value, int dwordValue);

    std::optional<int> RegGetDword(HKEY hKey, const std::string& subKey, const std::string& value);
    void RegSetDword(HKEY hKey, const std::string& subKey, const std::string& value, DWORD dwordValue);

    inline std::wstring utf8_to_wide(std::string_view utf8Text) {
         if (utf8Text.empty()) {
             return {};
         }

         std::wstring wideText;
         const int wideLength = ::MultiByteToWideChar(CP_UTF8, 0, utf8Text.data(), (int)utf8Text.size(), nullptr, 0);
         if (wideLength == 0) {
             DEBUG_PRINT("utf8_to_wide get size error.");
             return {};
         }

         // MultiByteToWideChar returns number of chars of the input buffer, regardless of null terminitor
         wideText.resize(wideLength, 0);
         const int length =
             ::MultiByteToWideChar(CP_UTF8, 0, utf8Text.data(), (int)utf8Text.size(), wideText.data(), wideLength);
         if (length != wideLength) {
             DEBUG_PRINT("utf8_to_wide convert string error.");
             return {};
         }

         return wideText;
     }

     inline std::string wide_to_utf8(std::wstring_view wideText) {
         if (wideText.empty()) {
             return {};
         }

         std::string narrowText;
         int narrowLength =
             ::WideCharToMultiByte(CP_UTF8, 0, wideText.data(), (int)wideText.size(), nullptr, 0, nullptr, nullptr);
         if (narrowLength == 0) {
             DEBUG_PRINT("wide_to_utf8 get size error.");
             return {};
         }

         // WideCharToMultiByte returns number of chars of the input buffer, regardless of null terminitor
         narrowText.resize(narrowLength, 0);
         const int length = ::WideCharToMultiByte(
             CP_UTF8, 0, wideText.data(), (int)wideText.size(), narrowText.data(), narrowLength, nullptr, nullptr);
         if (length != narrowLength) {
             DEBUG_PRINT("wide_to_utf8 convert string error.");
             return {};
         }

         return narrowText;
     }

} // namespace openxr_api_layer::utils::general
