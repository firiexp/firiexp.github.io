---
layout: post
title: Number Theoretic Transform
date: 2019-08-16
category: 数学
tags: 数学
---

## 説明
素数$p$に対して、原始n乗根$x$があれば、$\{x^0, x^1, \cdots , x^{n-1}\}$が位数nの巡回群になるので、FFTと同じように畳み込みができる。
{% include a.html code="ntt.cpp" %}