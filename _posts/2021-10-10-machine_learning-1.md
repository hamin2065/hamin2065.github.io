---
layout: post
title: "[Pandas] 기초 #2"
subtitle:
categories: ai
tags: machine-learning
---

# 데이터프레임 조건 및 필터링

df에서 `age`가 30이상인 사람만 가져올 수 있다.

```py
df['age'] >= 30
```

위의 형태로 출력해보면 Boolean으로 표시되는 시리즈가 출력된다.

```py
df[df['age'] >= 30]
```

이 처럼 또 다시 데이터프레임 안에 넣어주어야한다.

---

`job`이 `intern`인 사람을 데이터프레임으로 출력해보자.

```py
df[df['job'] == 'intern']
```

---

**AND 연산자(&)**
`age`가 30대 이상, 40대 이하인 사람

```py
df[(df['age'] >= 30) & (df['age'] <= 40)]
```

---

**OR 연산자(|)**
`age`가 30대 미만 혹은 40대 초과

```py
df[(df['age']<30) | (df['age'] > 40)]
```

---

**in 연산자(in)**

```py
df[df['job'].apply(lambda x : x in ['student', 'manager'])]
```

`lambda`와 `apply`를 통해서 `job`이 `student`와 `manager`인 것을 뽑아준다.

---

**Column 값을 변경**

```py
df['age'] = 20
```

`age`컬럼의 전체 값을 `20`으로 바꾼다.

`loc`을 사용해서 특정 값만 지정해서 바꿀 수도 있다.

```py
df.loc[2, 'age'] = 27
```

---

# DataFrame 그룹 생성(groupby)

실습에서 사용할 데이터를 새롭게 불러온다.

```py
abalone_df = pd.read_csv('./drive/MyDrive/machine_learning_data/abalone.data', header=None, sep=',',
                         names = ['sex', 'length', 'diameter', 'height',
                                  'whole_weight','shucked_weight', 'viscera_weight',
                                  'shell_weight', 'rings'])
```

---

**데이터의 shape를 확인**

```py
abalone_df.shape
```

---

**결측값 확인**

```py
abalone_df.isnull()
```

위 명령어를 통해서 각 값이 결측치인지 Boolean 형태로 표현하고 `.sum`을 사용하면 결측치의 개수를 더해서 시리즈 형태로 출력한다. 한 번더 `.sum`을 하면 전체 데이터에서 결측치의 값이 몇 개인지 검사할 수 있다.

**기술통계 확인**
: 연속형(numerical) 변수만 확인이 가능하다.

```py
abalone_df.describe()
```

## groupby

기본 구조 : `DataFrame[집계변수].groupby(DataFrame[집계대상])`
성별에 따른 무게를 집계해보자.

```py
grouped = abalone_df['whole_weight'].groupby(abalone_df['sex'])
```

`grouped`를 출력해보면 Object가 만들어진 것을 확인할 수 있다.

`sum()`함수를 이용하면 성별에 따른 무게의 합을 알 수 있다.

```py
grouped.sum()
```

`mean()`함수와 `size()`함수로 평균과 사이즈를 확인할 수 있다.

```py
grouped.mean()
```

```py
grouped.size()
```

---

그룹변수가 하나가 아닌 전체 연속형 변수에 대해서 집계를 해보자.

```py
abalone_df.groupby(abalone_df['sex']).mean()
```

밑에 처럼 간단하게 표현할 수도 있다.

```py
abalone_df.groupby('sex').mean()
```

**새로운 열 추가**
새로운 열을 추가해서 계산해보자.

```py
abalone_df['length_bool'] = np.where(abalone_df['length'] > abalone_df['length'].median(),
                                     'length_long', # true인 경우
                                     'length_short') # false인 경우
```

`>`조건이 true인 경우에는 `length_long`으로 출력되고 false라면 `length_short`로 출력된다.

위에서 생성한 열을 이용해서 그룹변수가 2개 이상일 때 선택해서 통계처리를 해보자.

```py
abalone_df.groupby(['sex','length_bool']).mean()
```

위의 명령어를 입력하면 전체 데이터프레임이 출력되는데 특정 컬럼만 지정해서 볼 수도 있다.

```py
abalone_df.groupby(['sex','length_bool'])['whole_weight'].mean()
```

---

# 중복 데이터

```py
new_abalone = abalone_df.iloc[[0]]
new_abalone_df = pd.concat([abalone_df, new_abalone], axis = 0)
new_abalone_df
```

첫 번째 행을 `concat`함수를 이용해서 `abalone_df`와 행 방향으로 연결해서 새로운 데이터프레임을 생성한다.

중복된 row를 확인하기 위해서 `duplicated()`함수를 사용한다.

```py
new_abalone_df.duplicated().sum()
```

`sum()`함수를 붙여서 개수를 세어볼 수 있다.

첫 번째 행과 마지막 행이 중복일 때 디폴트값으로는 마지막에 나오는 값이 True라고 표현되는데 `keep=last` 옵션을 넣으면 처음에 나타나는 행을 중복이라고 표시해준다.

```py
new_abalone_df.duplicated(keep='last')
```

`drop_duplicates()`함수를 이용하면 중복 데이터의 행을 삭제할 수 있다.

```py
new_abalone_df = new_abalone_df.drop_duplicates()
```

# 결측치 채우기

첫 번째 방법으로는 그냥 특정값을 지정해서 채울 수 있다.

```py
zero_abalone_df = nan_abalone_df.fillna(0)
```

아니면 값을 계산해서 의미있는 값을 집어넣을 수 있다.

```py
nan_abalone_df.fillna(nan_abalone_df.mean())
```

---

# apply 함수

**집계**
열을 기준으로 집계할 때 `apply`함수 사용이 가능하다.

```py
abalone_df[['diameter']].apply(np.average, axis = 0)
```

행을 기준으로 집계할 때도 `apply`함수를 사용할 수 있다.

```py
abalone_df[['diameter', 'whole_weight']].apply(np.average, axis = 1)
```

사용자 함수를 통해서 집계할 수도 있다.

```py
import math
def avg_ceil(x,y,z):
  return math.ceil((x+y+z)) #ceil -> 올림

abalone_df[['diameter', 'height', 'whole_weight']].apply(lambda x:avg_ceil(x[0],x[1],x[2]),axis = 1)
```

여기서 lambda에 들어가는 x는 하나의 행이다.

---

# 데이터프레임 합치기

`concat`함수를 이용해서 여러개의 데이터프레임을 합칠 수 있다.

```py
pd.concat([abalone_df, one_abalone_df], axis = 0)
```

열 방향으로 붙이는 것도 가능하다.

```py
pd.concat([abalone_df, one_abalone_df], axis = 1)
```
