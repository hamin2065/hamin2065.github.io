---
layout: post
title: "[Matplotlib & Seaborn] 데이터 시각화"
subtitle:
categories: ai
tags: machine-learning
---

**Matplotlib**

파이썬으로 기본적인 차트들을 쉽게 그릴 수 있도록 도와주는 시각화 라이브러리

**Seaborn**

matplotlib 기반으로 만들어진 통계 데이터 시각화 라이브러리

# 데이터 시각화 준비

```python
import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import seaborn as sns
import warnings

plt.rcParams['figure.figsize'] = [10, 8] # 가로10 세로8
sns.set(style='whitegrid')
sns.set_palette('pastel')
warnings.filterwarnings('ignore')
```

필요한 라이브러리와 모듈들을 import 시키고 차트를 그릴 기본 세팅을 해준다.

버전 문제에 따라서 경고가 뜨는데 무시하기 위해서 warnings를 `ignore`해준다.

한글이 깨지는 경우가 많기 때문에 그 경우를 대비해서 코드를 작성해준다. 밑의 코드는 외울 필요 없이 필요할 때 복붙해서 사용한다.

```python
# % 한글이 깨지는 경우 %
from matplotlib import font_manager, rc
import matplotlib
import platform

if platform.system() == 'Windows':
  # 윈도우인 경우
  font_name = font_manager.FontProperties(fname='c:/Windows/Fonts/malgun.ttf')
  rc('font', family = font_name)
else:
  # Mac인 경우
  rc('font', family = 'AppleGothic')

matplotlib.rcParams['axes.unicode_minus'] = False
```

seaborn에 있는 `tips`라는 데이터셋을 가져와서 사용한다.

```python
# Loading 'Tips' dataset from seaborn
tips = sns.load_dataset('tips')
tips.head()
```

전 시간에 배웠던 groupby를 통해서 `day`별로 `tip`의 합계를 계산해서 새로운 데이터셋을 만든다.

```py
sum_tip_by_day = tips.groupby('day')['tip'].sum()
sum_tip_by_day
```

`x`축에 쓰일 라벨도 미리 만들어둔다.

```py
x_label = ['Thu', 'Fri', 'Sat', 'Sun']
x_label_index = np.arange(len(x_label))
x_label_index
```

---

# Bar 차트 이해 및 제작

## matplotlib를 이용한 시각화

```py
plt.bar(x_label, sum_tip_by_day,# x축, y축
        color='pink', # 색 지정
        alpha=0.6, # 색 투명도
        width=0.3, # 너비
        align='edge') # 배치
plt.title('Sum Of Tips by Days')
plt.xlabel('Days', fontsize=14)
plt.ylabel('Sum of Tips', fontsize=14)
plt.xticks(x_label_index,
           x_label,
           rotation=45,
           fontsize=15)
plt.show()
```

`plt.bar`를 통해서 bar차트를 만들 수 있다. 다양한 옵션을 넣을 수 있고 `title`과 `label`을 지정할 수 있다. `xticks`를 통해서 x축의 라벨을 로테이트 시켜서 볼 수 있다.

그냥 출력해도 그래프가 나오지만 다른 부가적인 것들 없이 그래프만 보기 위해서 `plt.show`를 사용해서 그래프를 확인하는 것을 권장한다.

---

## seaborn을 이용한 시각화

```py
sns.barplot(data=tips, # 데이터 프레임
            x = 'day', # x 변수
            y = 'tip', # y 변수
            estimator = np.average,
            hue='sex', # 색깔 구분으로 특정 컬럼값을 비교하고 싶을 때
            order=['Sun','Sat','Fri','Thur'], # x ticks 순서
            edgecolor='.6', # 바 모서리 선명도
            linewidth=2.5) # 모서리 두께
plt.title('Sum Of Tips by Days')
plt.xlabel('Days', fontsize=14)
plt.ylabel('Average of Tips', fontsize=14)
plt.xticks(rotation=45)
plt.show()
```

`plt`와 비슷한 방식으로 사용하지만 `data` 라는 속성에 집어넣는 등 옵션이 조금 다르다.

`title`과 `label`관련해서 값을 줄 때는 `plt`를 사용해서 지정해주고 `plt.show`를 통해서 출력해준다.

---

# Pie 차트 이해 및 제작

```py
sum_tip_by_day = tips.groupby('day')['tip'].sum()
ratio_tip_by_day = sum_tip_by_day/sum_tip_by_day.sum() # 각각의 비율 구하기
```

파이 차트를 이용하기 위해서는 비율이 필요하기 때문에 비율을 구해서 새로운 데이터를 만들어준다.

## matplotlib를 이용한 시각화

```py
plt.pie(ratio_tip_by_day, # 비율 값
        labels = x_label, # 라벨값
        autopct='%.2f%%',# 부채꼴 안에 표시될 숫자 형식(소수점 두 자리까지 표시)
        startangle=90, # 축이 시작되는 각도 설정
        counterclock=True, # True -> 라벨 순서대로 / False -> 반시계방향
        explode=[0.05, 0.05, 0.05, 0.05], # 중심에서 얼마나 떨어져있는지
        shadow = True, # 그림자 표시 여부
        colors=['gold','silver','whitesmoke','gray'], # 색깔
        wedgeprops={'width':0.7, 'edgecolor':'w','linewidth':3}) # 도넛 차트를 그릴 때 사용하는 옵션들
plt.show()
```

시각화를 하기 위해서 다양한 옵션들을 적용할 수 있다.
Pie 차트 또한 `plt.show`를 통해서 나타내준다.

---

# Line 차트 이해 및 제작

line 차트 예제를 위해서 tips데이터에 가상 시간 컬럼을 추가해서 일요일에 해당하는 데이터만 사용해준다.

```py
sun_tips = tips[tips['day'] == 'Sun']
sun_tips
```

현재 서버 시간을 얻기 위해서 datetime 라이브러리를 사용해준다.

```py
import datetime

date=[]
today = datetime.date.today()
date.append(today)

for time in range(sun_tips.shape[0]-1):
  today += datetime.timedelta(1) # 하루씩 추가
  date.append(today)
date
```

`datetime.date.today()`를 통해서 오늘의 날짜를 출력할 수 있다. 오늘의 날짜를 시작으로 하루씩 추가해서 `date`리스트에 추가해준다.

`date`리스트를 만든 후에 `sun_tips`데이터에 `date`라는 컬럼을 추가해서 리스트에 있는 값들을 넣어준다.

```py
sun_tips['date'] = date
sun_tips
```

---

## matplotlib를 이용한 시각화

```py
plt.plot(sun_tips['date'],sun_tips['total_bill'],
         linestyle='-', # 라인 모양
         linewidth=2, # 라인 두께
         color='pink', # 색상 선택
         alpha=0.5,# 투명도
         )
plt.title('Total Tips by Date',fontsize=20)
plt.xlabel('date', fontsize=15)
plt.ylabel('total tip', fontsize=15)
plt.xticks(rotation=90)
plt.show()
```

`x`축과 `y`축에 넣을 데이터를 지정해주고 라인 모양, 라인 두께등에 대한 다양한 옵션을 적용해준다. 그리고 `title`과 `label`을 지정해서 그래프를 완성시킨다.

---

## seaborn을 이용한 시각화

```py
sns.lineplot(data=sun_tips,
             x = 'date',
             y = 'total_bill',
             hue='sex')
plt.title('Total Bill by date&sex',fontsize=20)
plt.show()
```

`lineplot`을 통해서 line차트를 만들 수 있다. `x`와 `y`라벡에 값을 넣고 `hue`속성을 통해서 성별에 따라 다른 색깔로 나타낼 수 있다.

---

# Scatter 차트 이해 및 제작

## matplotlib를 이용한 시각화

```py
plt.scatter(tips['total_bill'],tips['tip'],
            color='pink', # 색상
            edgecolor='black', # 테두리 색깔
            linewidth=2# 라인 두께
            )
plt.show()
```

`plt.scatter`을 통해서 scatter차트를 나타낼 수 있다. 다양한 옵션을 주어서 그래프를 만들 수 있다.

---

## seaborn을 이용한 시각화

```py
sns.scatterplot(data=tips,
                x = 'total_bill',
                y = 'tip',
                style='time', #모양 구분으로 다른 변수랑 비교 -> style
                hue = 'day',# 색깔 구분으로 다른 변수랑 비교 -> hue
                size = 'size', # 크기 구분으로 다른 변수랑 비교 -> size
                )
plt.title('Scatter  between total_bill and tip',fontsize=20)
plt.xlabel('total_bill', fontsize=16)
plt.ylabel('tip', fontsize=16)
plt.show()
```

`style`, `hue`, `size`속성을 통해서 다른 변수와 구분할 수 있다 .

---

# Heatmap 차트 이해 및 제작

상관계수에 관해서 차트를 그리는 것이다 .

```py
tips.corr()
```

를 통해서 상관계수를 구해볼 수 있는데 이 때, 상관계수는 연속형 변수에 대해서만 사용이 가능하다.
출력해보면 대각선에는 전부 `1`로 뜨는데 자기 자신과의 상관계수는 무조건 `1`로 나타나기 때문에 무조건 `1`이다

---

## seaborn을 이용한 시각화

```py
sns.heatmap(tips.corr(),
            annot = True, # 해당하는 상관관계의 크기를 나타냄
            square = True, # 정사각형으로 만들어준다.
            vmin=-1,vmax=1, # 최소 최댓값 지정
            linewidth=.5, # 라인 두께 지정
            cmap='RdBu', # 색깔테마
            )
```

위에서 구한 `tips.corr()`를 넣어주고 다양한 옵션을 주어서 히트맵을 그려준다.

---

# Histogram 차트 이해 및 제작

## matplotlib를 이용한 시각화

```py
plt.hist(tips['total_bill'],
         bins=30, # x축 나눌 개수
         density=True, # 비율적으로 나타냄
         alpha = 0.7, # 투명도
         color='pink', # 색깔
         edgecolor='black', # 테두리 색깔
         linewidth=0.9) # 테두리 두께
plt.title('Histogram for total_bill')
plt.xlabel('total_bill')
plt.ylabel('rate')

plt.show()
```

`plt.hist`를 통해서 히스토그램을 그려준다. `density=False`를 통해서 비율로 나타낼 수 있다. 테두리에 색깔을 주어서 더욱 뚜렷하게 나타내게 한다.

---

## seaborn을 이용한 시각화

```py
sns.histplot(data = tips,
             x = 'total_bill',
             bins=30,
             kde = True, # kernel density estimator
             hue = 'sex',
             multiple = 'stack',
             shrink = 0.6
             )
plt.title('Histogram for total_bill by sex')
plt.xlabel('total_bill')
plt.ylabel('rate')

plt.show()
```

`kde`라는 속성에 `True`값을 줘서 전체적인 분포를 선형태로 표현할 수 있다. `hue`옵션을 통해서 성별을 색깔로 구분하고 `multiple`에 `stack`또는 `dodge`속성을 줄 수 있는데 `stack`은 쌓아서 나타내주고 `dodge`는 겹치지 않게 옆으로 나열해서 보여준다.

---

# Box 차트 이해 및 제작

## matplotlib를 이용한 시각화

```py
plt.boxplot(tips['tip'],
            sym='rs')
plt.title('Box Plot for Tip',fontsize=20)
plt.xlabel('tip',fontsize=15)
plt.ylabel('tip size', fontsize=15)
plt.show()
```

`Box`차트를 그리는데 `sym`을 통해서 울타리 밖의 값들을 `rs`, 즉 빨간색(red), 사각형(square)형태로 나타낼 수 있다.

---

## seaborn을 이용한 시각화

```py
sns.boxplot(data=tips,
            x = 'day',
            y = 'tip',
            hue='smoker',
            linewidth=3,
            order=['Sun','Sat','Fri','Thur'])
plt.title('Box Plot for Tip by Day',fontsize=20)
plt.ylabel('tip',fontsize=15)
plt.show()
```

`seaborn`을 이용해서도 박스차트를 그릴 수 있다. `order`옵션을 통해서 요일별로 박스차트를 그릴 수 있고 `hue`속성을 통해서 색깔 구분을 해서 나타낼 수 있다.
