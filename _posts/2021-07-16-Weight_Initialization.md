---
layout: post
title:  Weight Initialization
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