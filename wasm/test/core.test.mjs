import assert from "node:assert/strict";
import fs from "node:fs";
import test from "node:test";
import path from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";

import { loadMethodius } from "../mefodij.js";

const here = path.dirname(fileURLToPath(import.meta.url));
const moduleUrl = pathToFileURL(
    path.resolve(here, "../../build/wasm/mefodij.js")
).href;

let methodius;

test.before(async () => {
    methodius = await loadMethodius(moduleUrl);
});

test("arithmetic and boolean expressions", () => {
    const math = methodius.eval("5 + 7 - 2 / 2 + 3 * 3;");
    assert.equal(math.ok, true);
    assert.equal(math.result, "20");
    assert.equal(math.output, "");
    assert.equal(math.error, "");

    const grouped = methodius.eval("(2 + 2) * 3 - 50 / 10;");
    assert.equal(grouped.result, "7");

    const logic = methodius.eval("(ні && 1) || (0 || так);");
    assert.equal(logic.result, "так");

    const compare = methodius.eval("1 < 1.15 && 2 >= 0.5 && 0.4 > 0.1;");
    assert.equal(compare.result, "так");
});

test("Ukrainian text, printing, and a fresh program on every call", () => {
    const printed = methodius.eval('друк "привіт\\n"; друк "світ";');
    assert.equal(printed.ok, true);
    assert.equal(printed.output, "привіт\nсвіт");
    assert.equal(printed.result, "світ");

    const length = methodius.eval("'привіт'.довжина;");
    assert.equal(length.result, "6");
    assert.equal(methodius.eval("'абв'[0];").result, "а");

    assert.equal(methodius.eval("мем секрет = 41;").ok, true);
    const leaked = methodius.eval("секрет;");
    assert.equal(leaked.ok, false);
    assert.match(leaked.error, /секрет/);
});

test("conditions, loops, and functions", () => {
    const branch = methodius.eval(
        "умова (1 > 2) { друк \"ні\"; } або { друк \"так\"; }"
    );
    assert.equal(branch.ok, true);
    assert.equal(branch.output, "так");

    const loop = methodius.eval(
        "мем рядок = \"аб\";\n" +
        "цикл (мем і = 0; і < рядок.довжина; і++) {\n" +
        "    друк рядок[і];\n" +
        "}"
    );
    assert.equal(loop.output, "аб");

    const stopped = methodius.eval(
        "мем д = 0;\n" +
        "цикл (так) {\n" +
        "    друк д;\n" +
        "    д++;\n" +
        "    умова (д >= 3) { стоп; }\n" +
        "}"
    );
    assert.equal(stopped.output, "012");

    const fn = methodius.eval(
        "мем тест = 3;\n" +
        "функція сума(а, б = 3) {\n" +
        "    вихід а + б + тест;\n" +
        "}\n" +
        "друк сума(3);"
    );
    assert.equal(fn.output, "9");
    assert.equal(fn.result, "9");
});

test("arrays, casts, regex, and comments", () => {
    const pair = methodius.eval(
        "мем мас = [10, 20, 30];\n" +
        "друк мас.перший;\n" +
        "друк мас.другий;\n" +
        "друк мас.розмір;"
    );
    assert.equal(pair.output, "10203");

    assert.equal(methodius.eval("вМасиві(7, [1, 7, 9]);").result, "так");
    assert.equal(methodius.eval("вМасиві(4, [1, 7, 9]);").result, "ні");
    assert.equal(methodius.eval("(ціле) 1.9;").result, "1");
    assert.equal(methodius.eval("'привіт світ' ~ '.*сві.*';").result, "так");
    assert.equal(methodius.eval("'привіт' ~ 'xyz';").result, "ні");

    const comment = methodius.eval("// лише коментар\n");
    assert.equal(comment.ok, true);
    assert.equal(comment.result, "");
});

test("errors keep earlier output and do not abort the module", () => {
    const divided = methodius.eval('друк "до"; 1 / 0;');
    assert.equal(divided.ok, false);
    assert.equal(divided.status, 1);
    assert.equal(divided.output, "до");
    assert.match(divided.error, /Division by zero/);

    const frozen = methodius.eval("конст а = 1; а = 2;");
    assert.equal(frozen.ok, false);
    assert.match(frozen.error, /const/);

    const empty = methodius.eval("");
    assert.equal(empty.ok, false);
    assert.match(empty.error, /Source file or code/);

    const again = methodius.eval("друк 1;");
    assert.equal(again.ok, true);
    assert.equal(again.output, "1");
});

test("імпорт reads only the in-memory filesystem", () => {
    const hostName = "mefodij-host-only.txt";
    fs.writeFileSync(hostName, 'друк "з диска";\n');
    try {
        const fromHost = methodius.eval('імпорт "mefodij-host-only.txt";');
        assert.equal(fromHost.ok, false);
        assert.match(fromHost.error, /mefodij-host-only\.txt/);
    } finally {
        fs.unlinkSync(hostName);
    }

    const missing = methodius.eval('імпорт "немає.txt";');
    assert.equal(missing.ok, false);
    assert.match(missing.error, /немає\.txt/);

    methodius.writeFile(
        "бібл/функції.txt",
        "функція додати(а, б) {\n    вихід а + б;\n}\n"
    );
    const imported = methodius.eval(
        'імпорт "бібл/функції.txt"; друк додати(20, 22);'
    );
    assert.equal(imported.ok, true, imported.error);
    assert.equal(imported.output, "42");

    methodius.writeFile("бібл/функції.txt", 'друк "оновлено";');
    const replaced = methodius.eval('імпорт "бібл/функції.txt";');
    assert.equal(replaced.output, "оновлено");
});
