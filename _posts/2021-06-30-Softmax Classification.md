---
layout: post
title:  Softmax Classification
subtitle:   
categories:  ai
tags: season-1
---




# Multinomial Classification

|x1(hours)|x2(attendance)|y(grade)|
|:---:|:---:|:---:|
|10|5|A|
|9|5|A|
|3|2|B|
|2|4|B|
|11|1|C|

위의 예시와 같이 A,B,C를 구분하는 상황이 있다.

![coding](/assets/img/posts/lec6_graph.jpg)

이 때 우리는 binary classification을 했을 때처럼 선을 그어서 분류를 할 수 있다.

위의 선은 각각 A or not(A이거나 아니거나), B or not(B이거나 아니거나), C or not(C이거나 아니거나)를 나타낸다.

여러개의 변수가 있는 상황에서는 아래의 식과 같이 벡터의 곱셈을 통해서 값을 예측한다.

![coding](/assets/img/posts/lec6_for1.jpg)

3개의 값을 예측해야하므로 위의 식을 3번을 써서 계산해야하는데, 밑의 식처럼 하나의 행렬로 써서 표현할 수 있다.

![coding](/assets/img/posts/lec6_for2.jpg)

$$\bar{y}_A$$ 에 2.0, $$\bar{y}_B$$ 에는 1.0 $$\bar{y}_C$$ 에 0.1의 값이 주어졌을 때 어떻게 0과 1사이로 나타낼 수 있을까?

이 때 사용하는 것이 Softmax 함수이다.

$$
S(y_i) = \frac{e^{y_i}}{\sum_{j}e^{y_i}}
$$

이 식을 이용해서 A, B, C에 대한 값은 0.7, 0.2, 0.1로 계산이 되고 `ONE-HOT ENCODING`을 통해서 A는 1.0 B와 C는 0.0의 값을 가지면서 a로 답이 나오게 된다.

# Cost Function

softmax classification에서 쓰는 Cost Function은 __CROSS-ENTROPY__ 이다.

이 식은 D(S, L) = $$-\sum_ {i} {L_i}\log({S_i}) $$ 이고 
S는 예측값, L은 실제 정답이다.

밑의 예시를 보면

![coding](/assets/img/posts/lec6_ex.jpg)

L이 실제 정답이고 이 정답이 B라고 나왔다고 가정하자.

1번은 L과 똑같이 B가 나오는데 Cost Function을 계산을 해보면 0이 나오고, 이와 다르게 2번은 무한대가 나오면서 cost값이 굉장히 크게 계산되는 것을 확인할 수 있다.

![coding](/assets/img/posts/lec6_cost.jpg)

training set이 많을 때 쓰는 cost function이다.

# Gradient Descent

마지막으로 cost값을 줄이기 위해서 미분을 통해서 기울기를 구하고 step의 크기를 곱해준다.

![coding](/assets/img/posts/lec6_gradient_descent.jpg)

참고

[ML lec 6-1 - Softmax Regression: 기본 개념 소개](https://www.youtube.com/watch?v=MFAnsx1y9ZI&list=PLlMkM4tgfjnLSOjrEJN31gZATbcj_MpUm&index=14)

[ML lec 6-2: Softmax classifier 의 cost함수](https://www.youtube.com/watch?v=jMU9G5WEtBc&list=PLlMkM4tgfjnLSOjrEJN31gZATbcj_MpUm&index=15)