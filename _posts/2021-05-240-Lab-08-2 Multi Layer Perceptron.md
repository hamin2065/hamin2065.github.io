---
layout: post
title: Lab-08-2 Multi Layer Perceptron
color: rgb(242,85,44)
tags: [AI, PyTorch]
---

# 학습목표
다중 퍼셉트론(Multi Layer Perceptron) 에 대해 알아본다.

# 핵심키워드
- 다중 퍼셉트론(Multi Layer Perceptron)
- 오차역전파(Backpropagation)

![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-01.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-02.jpg)


# Multi Layer Perceptron
 : 퍼셉트론에서 결과값을 내놓는 부분은 활성 함수인데 단층 퍼셉트론에서는 1개의 활성함수만을 갖는다. 단층 퍼셉트론은 비선형적으로 분리되는 데이터에 대해서는 제대로된 학습이 불가능하다는 한계가 있다. (예시) XOR)

 이를 극복하기 위해서 입력층과 출력층 사이에 하나 이상의 중간층을 두어서 비선형적으로 분리되는 데이터에 대해서도 학습이 가능하도록 다층 퍼셉트론(MLP)이 고안되었다. 

 입력층과 출력층 사이에 존재하는 중간층을 숨어 잇는 층이라고 해서 Hidden Layer(은닉층)이라고 부른다. 
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-04.jpg)

# Backpropagation
: `Artificial Neural Network`를 학습시키기 위한 일반적인 알고리즘중 하나이다. 한국말로 직역하면 `역전파`라는 뜻인데 찾고자 하는 `target값`과 실제 모델이 계산한 `output`이 얼마나 차이가 나는지 구한 후 그 오차값을 다시 위로 전파해 가면서 각 노드가 가지고 있는 변수들을 갱신하는 알고리즘이다. 
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-05.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-06.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-07.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-08.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-09.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-10.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-11.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-12.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-13.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-14.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-15.jpg)
![coding](../../../assets/img/posts/Lab-08-2MultiLayerPerceptron-16.jpg)