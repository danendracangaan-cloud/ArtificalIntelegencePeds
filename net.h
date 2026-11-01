// net.h - HTTP POST polos (tanpa TLS) ke proxy milik lu sendiri. Proxy yang urus HTTPS ke API LLM.
#pragma once
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

inline bool http_post(const std::string& host, const std::string& port, const std::string& path,
                      const std::string& body, std::string& outBody, int timeoutSec = 12) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC; hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0 || !res) return false;
    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (fd < 0) { freeaddrinfo(res); return false; }
    timeval tv{timeoutSec, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
    if (connect(fd, res->ai_addr, res->ai_addrlen) != 0) { close(fd); freeaddrinfo(res); return false; }
    freeaddrinfo(res);
    std::string req = "POST " + path + " HTTP/1.0\r\nHost: " + host +
        "\r\nContent-Type: text/plain; charset=utf-8\r\nContent-Length: " + std::to_string(body.size()) +
        "\r\nConnection: close\r\n\r\n" + body;
    if (send(fd, req.data(), req.size(), 0) < 0) { close(fd); return false; }
    std::string resp; char buf[1024]; ssize_t n;
    while ((n = recv(fd, buf, sizeof buf, 0)) > 0) resp.append(buf, n);
    close(fd);
    size_t p = resp.find("\r\n\r\n");
    if (p == std::string::npos) return false;
    outBody = resp.substr(p + 4);
    return !outBody.empty();
}
