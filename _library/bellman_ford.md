---
layout: post
title: 単一始点最短路(Bellman-Ford法)
date: 2018-04-28
category: グラフ
tags: グラフ
---

## 説明
単一始点最短路を求める。Dijkstra法とは異なり、閉路があっても正しく動作する。$O(VE)$
{% include a.html code="bellman_ford.cpp" %}