---
layout: post
title:  Backpropagation
subtitle:   
categories:  ai
tags: season-1
---

# Backpropagation
타겟값이랑 모델의 결과값이랑 차이가 얼마나 있는지 계산후 오차값을 다시 뒤로 전파해나가면서 weight값을 업데이트 시키는 과정이다.

![backpropagation](https://blog.kakaocdn.net/dn/bCZail/btqIYaSTtFz/pNUkommeWjsYdVo19C5DU1/img.png)

__f(x,y,z) = (x + y) * z__

q = x+y

f = qz

위의 식이 있고 미지수의 값은 각각
x = -2, y = 5, z = -4 이다.


이 때, q의 값은 3이고 f의 값은 -12이다.

주어진 x,y,z의 값으로 q와 f의 값을 계산한 것을 __Forward Pass__ 라고 부른다.

${\operatorname{d}\!q\over\operatorname{d}\!x}$ = 1

${\operatorname{d}\!q\over\operatorname{d}\!y}$ = 1

${\operatorname{d}\!f\over\operatorname{d}\!q}$ = z = -4

${\operatorname{d}\!q\over\operatorname{d}\!z}$ = q = (x+y) = (-2+5) = 3


궁극적으로 구하려는 것은
${\operatorname{d}\!f\over\operatorname{d}\!x}$ 이다.

직접적으로 구할 수는 없지만 전에 구해놓은 값들을 이용하면 ${\operatorname{d}\!f\over\operatorname{d}\!x}$ = ${\operatorname{d}\!f\over\operatorname{d}\!q}$ * ${\operatorname{d}\!q\over\operatorname{d}\!x}$ = -4 * 1 = -4으로 값을 구할 수 있다.

또한 y에 따른 f의 기울기도 위와 같은 방식으로 구할 수 있다.

${\operatorname{d}\!f\over\operatorname{d}\!y}$ = ${\operatorname{d}\!f\over\operatorname{d}\!q}$ * ${\operatorname{d}\!q\over\operatorname{d}\!y}$ = (-4) * (1) = -4

- - -
Forward Pass를 할 때 우리는 Local Gradient를 미리 구해서 저장할 수 있다. 앞에서 본 예시처럼 ${\operatorname{d}\!q\over\operatorname{d}\!x}$ 와 ${\operatorname{d}\!q\over\operatorname{d}\!y}$ 를 먼저 구한 것이다.

우리가 최종적으로 구하고 싶은 것은 ${\operatorname{d}\!Loss\over\operatorname{d}\!x}$, 즉 x에 따른 Loss의 기울기를 알고 싶은 것이다. 이때, 우리는 복잡하게 계산하는 것이 아니라 Global Gradient인 ${\operatorname{d}\!Loss\over\operatorname{d}\!q}$ 와, ${\operatorname{d}\!q\over\operatorname{d}\!x}$ 를 곱해서 위에서 구하자고 한 값을 계산할 수 있는 것이다.

결국 Backpropagation은 Chain Rule을 사용해서 Local Graident * Global Gradient를 곱해서 계산하는 것이다.

결론
- 아무리 깊고 복잡한 층으로 구성되어 있다 하더라도 __Chain Rule__ 을 활용해서 미분 값을 얻어낼 수 있다.
- Forward Pass시 __Local Gradient__ 를 미리 계산해서 저장해 둔다.
- 저장해둔 __Local Gradient__ 와 __Global Gradient__ 를 __Backward Pass__ 할 때에 곱하여서 최종 미분 값을 얻는다.

[참고](https://www.youtube.com/watch?v=1Q_etC_GHHk)