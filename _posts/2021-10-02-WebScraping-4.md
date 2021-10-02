---
layout: post
title: "[웹 스크래핑] User Agent"
subtitle:
categories: data
tags: web-scraping
---

[Whatismybrowser](https://www.whatismybrowser.com/detect/what-is-my-user-agent) 에서 자신의 User Agent를 확인할 수 있다.

```py
import requests
url = "http://nadocoding.tistory.com"
headers = {"User-Agent":"자신의 User-Agent"}
res = requests.get(url, headers=headers) # headers에 user agent값 넘겨주기
res.raise_for_status()

with open("nadocoding.html","w",encoding="utf8") as f:
    f.write(res.text)
```

user agent를 가져와서 headers에 넣고 코드를 돌려보면 user agent가 없을 때는 정보가 다 나오지 않았지만 user agent가 있을 때는 훨씬 더 많은 정보가 들어있는 `nadocoding.html`파일이 만들어진 것을 확인할 수 있다.
