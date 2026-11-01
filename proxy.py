#!/usr/bin/env python3
"""Proxy AI untuk InteractivePeds. Jalanin di PC/VPS:  ANTHROPIC_API_KEY=sk-... python3 proxy.py
Terima prompt teks dari mod, balas:
  baris 1: dHappy,dAnger,dFear  (perubahan mood, -20..20)
  baris 2+: balasan ped (singkat, gaya bicara jalanan)
"""
import json, os, re, urllib.request
from http.server import BaseHTTPRequestHandler, HTTPServer

API_KEY = os.environ["ANTHROPIC_API_KEY"]
MODEL = os.environ.get("MODEL", "claude-haiku-5-5")
SYSTEM = ("Kamu memerankan NPC di GTA San Andreas. Balas SINGKAT (maks 2 kalimat), bahasa Indonesia gaul, "
          "sesuai kepribadian dan mood yang diberikan. Jangan keluar dari karakter. "
          "Output HARUS format:\n<dHappy>,<dAnger>,<dFear>\n<balasan>\n"
          "dengan tiga angka bulat -20..20 = perubahan mood setelah mendengar ucapan player.")

def ask(prompt):
    body = json.dumps({"model": MODEL, "max_tokens": 150, "system": SYSTEM,
                       "messages": [{"role": "user", "content": prompt}]}).encode()
    req = urllib.request.Request("https://api.anthropic.com/v1/messages", body, {
        "x-api-key": API_KEY, "anthropic-version": "2023-06-01", "content-type": "application/json"})
    with urllib.request.urlopen(req, timeout=10) as r:
        return json.load(r)["content"][0]["text"].strip()

class H(BaseHTTPRequestHandler):
    def do_POST(self):
        prompt = self.rfile.read(int(self.headers.get("Content-Length", 0))).decode("utf-8", "ignore")
        try:
            out = ask(prompt)
            if not re.match(r"^-?\d+,-?\d+,-?\d+\n", out):
                out = "0,0,0\n" + out
        except Exception as e:
            out = "0,0,0\n..."; print("err", e)
        data = out.encode()
        self.send_response(200); self.send_header("Content-Length", str(len(data))); self.end_headers()
        self.wfile.write(data)

HTTPServer(("0.0.0.0", 8787), H).serve_forever()
