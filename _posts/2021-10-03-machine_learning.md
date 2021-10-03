---
layout: post
title: "[Pandas] 기초 #1"
subtitle:
categories: ai
tags: machine-learning
---

# Series 실습

```py
import numpy as np
np.array([1,2,3])
```

`numpy`를 불러와서 array를 통해 시리즈를 만들 수 있다.

하나의 집합으로 볼 수 있는 데이터프레임에서 특정 컬럼을 선택해서 시리즈를 만들 수도 있다.

```py
series = df['name']
```

또한, 판다스의 `Series`함수를 통해서 만드는 것도 가능하다.

```py
series = pd.Series([1,2,3,4])
```

`Series`함수를 이용하는 경우에는 다양한 옵션을 줄 수가 있다.

```py
series = pd.Series([1,2,3,4], index = ['a','b','c','d'],dtype = float)
```

- `index` : 할당값의 지정 이름. 중복이 가능
- `dtype` : 데이터의 자료형

정렬되지 않은 자료를 정렬하고 싶을 때는 `sort_values()`라는 함수를 쓴다.

```py
series = pd.Series([10,2,5,4],index = ['a','b','c','d'], dtype=float)
series.sort_values(ascending=True) # 오름차순, 변수할당 x
```

이 때, `ascending = True`가 디폴트 값이기 때문에 내림차순으로 하고 싶으면 `ascending = False`를 넣어주면 된다.

value가 아닌 index를 sort하고 싶으면 `sort_index()`함수를 써준다.

```py
series = pd.Series([10,2,5,4],index=['z','f','c','d'],dtype=float)
series.sort_index()
```

---

# DataFrame 실습

1. 딕셔너리를 사용해서 데이터프레임을 만들 수 있다.

```py
df = pd.DataFrame({'a':[2,3],'b':[5,10]})
```

2. 리스트를 사용할 수도 있다.

```py
df = pd.DataFrame([[2,5],[3,10],[10,20]],columns=['a','b'])
```

여러개의 옵션을 통해서 column 이름과 index를 지정할 수 있고 dtype을 통해서 data type 지정이 가능하다.

```py
df = pd.DataFrame([[2,5],[3,10],[10,20]],columns=['a','b'],index=['가','나','다'],dtype=float)
```

---

# DataFrame 행, 열 선택 및 필터링

원하는 데이터를 `read_csv()`함수로 불러온다.

```py
df = pd.read_csv(friend_src,encoding='utf-8')
```

**iloc**

```py
df.iloc[2]
```

index 2번에 해당하는 행을 가져온다.

```py
df.iloc[[2]]
```

`[]`를 하나 더 쓰면 데이터프레임 형태로 가져온다.

여러개의 행을 쉼표를 통해서 구분해주면 여러행을 가져올 수 있다.

```py
df.iloc[[2,3]]
```

`:`를 통해 슬라이싱 기능도 사용이 가능하다.

```py
df.iloc[2:4]
```

행만 슬라이싱 하는 것이 아니라 행과 열을 동시에 추출 할 수 있다.

```py
df.iloc[:,[1,2]]
df.iloc[:,1:3]
```

---

컬럼 이름을 써서 컬럼 전체를 가져올 수 있다.

```py
df['job']
```

원하는 데이터프레임의 `job` 컬럼을 가져올 수 있다.

---

**loc**

```py
df.loc[:,'job']
```

`loc`는 index가 아닌 데이터프레임에 있는 이름을 써주면 된다.

---

# DataFrame 행, 열 삭제

```py
import numpy as np
df = pd.DataFrame(np.arange(12).reshape(3, 4),
                  columns=['A', 'B', 'C', 'D'])
```

`numpy`를 통해서 시리즈를 만들고 `reshape`를 통해서 행렬로 만들어주고 DataFrame으로 만들어준다.

```py
df.drop(['B', 'C'], axis=1)
```

`axis = 1`은 컬럼 방향이로 `axis = 0`은 행방향이다. 위의 코드는 컬럼 방향으로 `B`와 `C`의 인덱스를 가진 컬럼을 `drop`시키겠다는 뜻이다. 디폴트 값은 `axis = 1`이다.

이 때, 원래의 df에는 적용이 되지 않기 때문에 `inplace = True`라는 옵션을 통해서 원래의 df에 적용할 수 있다.

---

# DataFrame 행, 열 수정

```py
df = pd.read_csv(friend_src,encoding='utf-8')
```

쓰고자하는 데이터프레임을 불러온다.

```py
df['age'] = 20
```

를 통해서 특정 컬럼의 전체 값을 변경시킬 수 있다.

```py
df.loc[2,'age'] = 15
```

`loc`를 써서 전체 컬럼이 아닌 특정 행의 특정 열값을 변경 시킬 수 있다.
