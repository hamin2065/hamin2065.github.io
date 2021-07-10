---
layout: post
title:  Application & Tips
subtitle:   
categories:  ai
tags: season-1
---

# Learning Rate
- Learning rate가 너무 큰 경우 : step이 매우 커져서 함수를 벗어날 수 있다.(바깥으로 튕겨나갈 수 있다.) 결과적으로 학습이 잘되지 않는다.
- Learning rate가 너무 작은 경우 : 너무 작은 step으로 움직이기 때문에 너무 오랜 시간이 걸린다.

=> 따라서 적당한 크기의 learning rate를 구하는 것이 중요한데, 우선 `0.01`로 설정해놓고 발산한다면 값을 줄이고, 너무 작게 움직인다면 값을 늘리는 방식을 추천한다.
- - -
# Data Preprocessing
값의 차이가 많이 큰 데이터셋을 학습시키는 경우 조금만 값을 잘못 설정해도 설정한 범위에서 벗어날 수 있기 때문에 normalize를 시켜야한다.

![coding](/assets/img/posts/lec7_data_preprocessing.png)
- `zero-centered data` : 데이터의 중심을 가운데(0,0)로 맞히는 것
- `normalized data` : 데이터 값 전체의 범위가 특정 범위안에 항상 들어오도록 하는 것

## Standardization
$$x'_j = {x_j - \mu_j\over{\sigma_j}}$$

위의 식을 python코드로 작성하면 다음과 같다.
```py
X_std[:,0] = (X[:,0] - X[:,0].mean()) / X[:,0].std()
```
- - -
# Overfitting
: training data set으로 과도하게 학습시켜서 (memorization) training dataset으로는 높은 정확도를 보이지만 test dataset이나 실제로 쓰이면 정확도가 높지 않다.

## Solutions for overfittin
1. More training data
1. Reduce the number of features
1. Regularization : 일반화

    -> weight값을 너무 크게 갖지 않도록 한다.

    -> 저번에 구한 L의 식에 $λ\log{W^2}$ 를 더해주면 된다.

    -> 이 식은 λ값이 0일 때는 L에 아무것도 더하지 않겠다는 것이고 λ의 값이 1일때는 아주 큰 값을 더하겠다는 뜻이다.

    -> 이때, λ를 regularization strength라고 부른다.
    
    -> 이 식을 python코드로 표현하면 다음과 같다.
    ```py
    l2reg = 0.001 * tf.reduce_sum(tf.square(W))
    ```

- - -
# Learning and Test data sets
training data set만 가지고 모델을 학습 시키고 그 data set으로 실제 test를 해보면 100퍼센트의 정확도가 나온다. 
하지만 우리는 모든 데이터를 외운 모델이 필요한 것이 아니라 새로운 데이터에 대해서 높은 정확도를 보이는 모델이 필요하다.

그렇기 때문에 주어진 데이터에서 training과 test set으로 나눠서 학습을 시킨다. 
training으로 학습을 시킨 모델을 test data set으로 실제 테스트를 해보는 것이다.

또는 앞에서 언급한 것처럼 적절한 α또는 λ를 구해야하는 경우가 있다. 이럴 때 training data set을 또 training과 validation dataset으로 나눠서 모의 시험을 통해 α와 λ를 튜닝해줄 수 있다.

*하나의 학습방법 예시로 `Online learning`이 있는데 이 학습방법은 데이터의 양이 너무 많아서 나눠서 학습시키는 방법이다. 이 때, 주의해야할 점은 전에 학습한 내용이 모델에 남아있는 상태로 새로운 것들을 학습해서 model에 추가하는 방식이라는 것이다.

참고

[lec 07-1: 학습 rate, Overfitting, 그리고 일반화 (Regularization)](https://www.youtube.com/watch?v=1jPjVoDV_uo&list=PLlMkM4tgfjnLSOjrEJN31gZATbcj_MpUm&index=18)

[lec 07-2: Training/Testing 데이타 셋](https://www.youtube.com/watch?v=KVv1nMSlPzY&list=PLlMkM4tgfjnLSOjrEJN31gZATbcj_MpUm&index=19)