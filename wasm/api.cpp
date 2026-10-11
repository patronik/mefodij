#include "mefodij_wasm.h"

#include "Engine.h"
#include "tools.h"

#include <cerrno>
#include <fstream>
#include <string>
#include <sys/stat.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define MEFODIJ_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define MEFODIJ_EXPORT
#endif

namespace {

std::string gOutput;
std::string gResult;
std::string gError;

void ensureParentDirs(const std::string & path)
{
    for (size_t i = 1; i < path.size(); i++) {
        if (path[i] != '/') {
            continue;
        }
        std::string dir = path.substr(0, i);
        if (dir.empty() || dir == ".") {
            continue;
        }
        if (::mkdir(dir.c_str(), 0777) != 0 && errno != EEXIST) {
            return;
        }
    }
}

}

extern "C" MEFODIJ_EXPORT int mefodij_eval(const char * utf8_code)
{
    gOutput.clear();
    gResult.clear();
    gError.clear();

    if (!utf8_code) {
        gError = "Code is missing.";
        return 2;
    }

    Mefodij::Engine engine;
    engine.setCapturePrint(true);
    try {
        auto value = engine.evaluateCode(std::string(utf8_code));
        gOutput = Mefodij::Tools::wideStrToStr(engine.getPrintBuffer());
        gResult = Mefodij::Tools::wideStrToStr(value->toString());
        return 0;
    } catch (const std::exception & error) {
        gOutput = Mefodij::Tools::wideStrToStr(engine.getPrintBuffer());
        gError = error.what();
        return 1;
    } catch (...) {
        gOutput = Mefodij::Tools::wideStrToStr(engine.getPrintBuffer());
        gError = "Unknown evaluation error.";
        return 1;
    }
}

extern "C" MEFODIJ_EXPORT const char * mefodij_output(void)
{
    return gOutput.c_str();
}

extern "C" MEFODIJ_EXPORT const char * mefodij_result(void)
{
    return gResult.c_str();
}

extern "C" MEFODIJ_EXPORT const char * mefodij_error(void)
{
    return gError.c_str();
}

extern "C" MEFODIJ_EXPORT int mefodij_write_file(
    const char * path,
    const char * utf8_contents
)
{
    if (!path || !path[0] || !utf8_contents) {
        return 2;
    }

    ensureParentDirs(path);
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        return 1;
    }
    out.write(utf8_contents, static_cast<std::streamsize>(std::char_traits<char>::length(utf8_contents)));
    return out.good() ? 0 : 1;
}
