---
layout: post
title: "[웹 스크래핑] Requests"
subtitle:
categories: data
tags: web-scraping
---

# Requests

`pip install requests`명령어를 통해서 설치를 진행해준다.

```py
import requests
res = requests.get("http://google.com")
print("응답코드 :",res.status_code)#200이면 정상
```

`응답코드 : 200`이 출력되면 정상 작동한 경우이다.

```py
if res.status_code == requests.codes.ok:print("정상입니다.")
else:print("문제가 생겼습니다. [에러코드 ",res.status_code,"]")
```

정상동작하는 경우와 에러가 생기는 경우를 조건문을 통해서 확인할 수 있다.

위의 과정처럼 조건문을 사용하지 않고

```py
res.raise_for_status()
```

를 사용하면 정상작동하는 경우(200)가 아니면 에러를 발생시킨다.

```py
print(len(res.text))
print(res.text)
```

가져오고자 하는 웹페이지의 텍스트 길이와 텍스트를 출력해본다.

양이 굉장히 많기 때문에 터미널 상으로는 보기 힘들다.

```py
with open("mygoogle.html","w",encoding="utf8") as f:
    f.write(res.text)
```

`mygoogle.html`이라는 파일을 생성해주고 브라우저를 통해 열어보면 스타일은 조금 다르지만 구글페이지와 같은 내용의 페이지가 열리는 것을 확인할 수 있다.
