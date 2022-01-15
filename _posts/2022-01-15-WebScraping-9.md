---
layout: post
title: "[웹 스크래핑] BeautifulSoup4 #5"
subtitle: "네이버 시가총액"
categories: data
tags: web-scraping
---

# 네이버 시가총액 가져오기

네이버 시가총액에 대한 정보를 csv파일로 저장하기 위해서 `csv`를 불러오고 다른 필요한 모듈들도 불러온다.

```py
import csv
import requests
from bs4 import BeautifulSoup
```

새로운 파일로 만들기 위해서 url과 `open`에 관한 코드를 작성해준다. csv파일로 저장하기 위해서 `writer`를 써준다.

```py
url = "https://finance.naver.com/sise/sise_market_sum.nhn?&page="

filename = "시가총액1-200.csv"
f = open(filename, "w", encoding="utf-8-sig", newline="")
writer= csv.writer(f)
```

시가 총액에 관한 내용을 불러오기 전에 각 열에 대한 정보를 title의 변수에 담고 리스트 형태로 `writer`에 집어넣어야하기 때문에 `split()`을 써준다.

```py
title = "N	종목명	현재가	전일비	등락률	액면가	시가총액	상장주식수	외국인비율	거래량	PER	ROE	토론실".split("\t")

writer.writerow(title)
``
```

마지막으로 원하는 정보들이 있는 태그를 찾아서 반복문을 통해 불러온다.

```py
for page in range(1,6):
    res = requests.get(url+str(page))
    res.raise_for_status()
    soup = BeautifulSoup(res.text, "lxml")

    data_rows = soup.find("table", attrs={"class":"type_2"}).find("tbody").find_all("tr")
    for row in data_rows:
        columns = row.find_all("td")
        if len(columns) <= 1:continue # 의미없는 data는 skip
        data = [column.get_text().strip() for column in columns] # strip()을 통해서 의미없는 공백 skip
        writer.writerow(data)
```

정상적으로 코드가 작성이 되면 `시가총액1-200.csv`파일이 생성되는 것을 볼 수 있다.
