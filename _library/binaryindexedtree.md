---
layout: post
title: BIT(BinaryIndexedTree)
date: 2018-04-28
category: データ構造
tags: データ構造
---

## 説明
可換群(逆元が存在する群)について、区間和を$O(\log N)$で求め、更新を$O(\log N)$で行う。<br>
可換でなくても$[0, x)$について演算した結果だけを求めたいのであれば、使うことができる。(例: LIS)
{% include a.html code="binaryindexedtree.cpp" %}