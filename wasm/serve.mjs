// Serves the repository so the browser can load the ES module and the wasm file.
import http from "node:http";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const port = Number(process.env.PORT || 8080);
const types = {
    ".html": "text/html; charset=utf-8",
    ".js": "text/javascript; charset=utf-8",
    ".mjs": "text/javascript; charset=utf-8",
    ".css": "text/css; charset=utf-8",
    ".wasm": "application/wasm",
    ".map": "application/json",
};

const server = http.createServer((request, response) => {
    const url = new URL(request.url, "http://127.0.0.1:" + port);
    let pathname = decodeURIComponent(url.pathname);
    if (pathname.endsWith("/")) {
        pathname += "index.html";
    }
    const file = path.normalize(path.join(root, pathname));
    if (file !== root && !file.startsWith(root + path.sep)) {
        response.writeHead(403);
        response.end("Forbidden");
        return;
    }
    fs.readFile(file, (error, data) => {
        if (error) {
            response.writeHead(404);
            response.end("Not found");
            return;
        }
        const type = types[path.extname(file)] || "application/octet-stream";
        response.writeHead(200, { "Content-Type": type });
        response.end(data);
    });
});

server.listen(port, "127.0.0.1", () => {
    console.log("http://127.0.0.1:" + port + "/wasm/example/");
});
