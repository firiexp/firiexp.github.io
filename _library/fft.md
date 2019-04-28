---
layout: post
title: 高速フーリエ変換
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
任意MODの畳み込みに対応するFFT。
$x = a \cdot 2^{15} + b$とし、$a$と$b$を別々に畳み込み合計する。このままでは4回の畳み込みが必要となるが、複素数領域を利用することで畳み込み回数を半分にしている。$O(N \log N)$。
{% include a.html code="fft.cpp" %}