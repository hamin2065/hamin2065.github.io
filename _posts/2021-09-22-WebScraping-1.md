---
layout: post
title: "[웹 스크래핑] Intro, Xpath"
subtitle:
categories: data
tags: web-scraping
---

# 스크래핑? 크롤링?

`웹 스크래핑` : 웹페이지에서 내가 **원하는 부분** 만 떼어오는 것

`웹 크롤링` : 페이지가 주어지면 페이지내에 있는 그 링크를 따라 **모든** 내용을 가져오는 것

우선, 웹 스크래핑을 하기 위해서는 웹을 어느정도 알아야한다.

---

# Xpath

HTML문서에서 특정 엘리먼트에 접근하기 위한 주소(경로)이다.

전체경로로 나타낼 수도 있고 아이디나 클래스의 속성을 이용해서 간편하게 표현할 수도 있다.

```txt
/html/body/div/span/a...
//*[@id="login"]
```
