---
layout: post
title: 階乗ライブラリ
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
$N!$までの$\mod M$とその逆元を$O(N + \log M)$で前計算する。これによって二項係数の計算を$O(1)$で行う。
{% include a.html code="factorial.cpp" %}