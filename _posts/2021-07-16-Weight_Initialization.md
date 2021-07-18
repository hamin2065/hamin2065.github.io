---
layout: post
title:  Weight Initialization, Dropout
subtitle:   
categories:  ai
tags: season-1
---

앞서 봤던 __Vanishing gradient__ 를 해결하는 한 가지 방법으로는 __ReLu__ 가 있었다.

또 다른 이유를 초기값에서 찾을 수 있다.

# 초기값을 0으로?
Weight값을 전부 0으로 준다면 어떻게 될까?
우리가 학습시키는 x가 학습을 진행하면서 W을 계속 쓰는데 이때 W의 값이 0이면 모든 값이 0이 나오기 때문에 gradient값이 사라지는 문제가 발생하게 된다.

# 초기값을 어떻게 설정해야할까?
2006년에 "A Fast Learning Algorithm for Deep Belief Nets"에서 소개한 `Restricted Boatman Machine(RBM)`이 등장했다. 
RBM을 통해서 초기화를 시킨 네트워크를 `Deep Belief Nets(DBN)`이라고 부른다.

![coding](/assets/img/posts/DBN.png)

왼쪽의 Forward부분에 안에 색깔이 칠해져있는 input layer과 Backward 부분에서 Backpropagation으로 다시 학습시켜서 돌아온 layer의 값의 차가 최소가 되도록 Weight값을 설정해주는 것이 DBN이다.

- - -

# Xavier Initialization

fan_in : input

fan_out : output
```py
W = np.random.randn(fan_in, fan_out)/np.sqrt(fan_in)
```

- - -

# He Initialization
```py
W = np.random.randn(fan_in, fan_out)/np.sqrt(fan_in/2)
```

# Overfitting

![overfitting](https://3gp10c1vpy442j63me73gy3s-wpengine.netdna-ssl.com/wp-content/uploads/2018/03/Screen-Shot-2018-03-22-at-11.22.15-AM-e1527613915658.png)
overfitting은 학습할 때, training data로 과하게 학습시키는 것이다. 이렇게 학습을 시키게 되면 training dataset에서는 좋은 성능을 보일 수 있어도 test dataset에서 좋지 않은 성능이 나타나게 된다.

# Dropout
위의 overfitting 문제를 해결하는 방법중 하나인 Dropout은 밑의 그림처럼 학습할 때 신경망의 뉴런을 부분적으로 생략해주는 것이다.
![dropout](https://miro.medium.com/max/981/1*EinUlWw1n8vbcLyT0zx4gw.png)

이 때 주의해야할 것은 training과정에서는 Dropout을 적용하지만 실제 test과정에서는 dropout을 적용하면 안된다.