---
layout: post
title: Radix-Heap
date: 2019-10-20
category: データ構造
tags: データ構造
---

## 説明
最大値$D$で、popされた数より小さな数がpushされないとき、優先度付きキューの各操作を$O(\log D)$で行う。
{% include a.html code="radixheap.cpp" %}