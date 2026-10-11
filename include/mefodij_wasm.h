#ifndef MEFODIJ_WASM_H
#define MEFODIJ_WASM_H

/* Browser entry points for the Methodius interpreter.
   Strings are UTF-8. Pointers returned by this API stay valid until the
   next call and are never null. The API is not reentrant. */

#ifdef __cplusplus
extern "C" {
#endif

/* Evaluate one program.
   Returns 0 on success, 1 when evaluation fails, 2 when code is null.
   On failure, mefodij_output() still holds any друк text produced before
   the error, and mefodij_error() explains it. Each call starts a fresh
   program; variables do not carry over. Files written with
   mefodij_write_file() do carry over. */
int mefodij_eval(const char * utf8_code);

const char * mefodij_output(void);
const char * mefodij_result(void);
const char * mefodij_error(void);

/* Write a UTF-8 file into the in-memory filesystem so імпорт can read it.
   Host directories are not visible. Returns 0 on success, 1 on I/O
   failure, 2 when an argument is missing or the path is empty.
   Forward slashes only. Parent directories are created. */
int mefodij_write_file(const char * path, const char * utf8_contents);

#ifdef __cplusplus
}
#endif

#endif
