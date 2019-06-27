---
layout: post
title: SegmentTree
date: 2018-04-29
category: データ構造
tags: データ構造
---

## 説明
要素がモノイドであり、更新があるときに、一点更新および区間取得を$O(\log N)$で行うデータ構造。
モノイドの条件は下の3つである。

1. 単位元が存在する(存在しない場合でも殆どの場合適切に加えればよい)
2. 結合則 $a \cdot (b \cdot c) = (a \cdot b) \cdot c​$が成立すること
3. 演算が閉じていること

この実装では、抽象化をモノイド構造体を渡すことによって行っている。fはマージするときの演算、eは単位元である。
{% include a.html code="segtree.cpp" %}