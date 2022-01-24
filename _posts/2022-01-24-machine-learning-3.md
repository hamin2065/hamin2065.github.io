---
layout: post
title: "[Matplotlib & Seaborn] 데이터 시각화"
subtitle:
categories: ai
tags: machine-learning
---

# 선형회귀

하나 이상의 특성과 연속적인 타깃 변수 사이의 관계를 모델링하는 것. 즉 연속적인 출력 값(돈, 키등)을 예측하는 것이다.

`Y = W0 + W1*X` -> 특성과 타깃 사이의 관계를 나타내는 선형 방정식의 가중치(W)를 학습하는 것이 목적!

## 선형 회귀 모델의 훈련과 비용함수

### 모델 훈련이란

- 모델이 훈련 데이터에 잘 맞도록 모델 파라미터를 설정하는 것
- 모델이 훈련 데이터에 얼마나 잘 들어맞는지 측정해야함

### 모델 훈련에 필요한 비용함수 종류

1. MSE(Mean Squared Error)

- 회귀 모델의 주요 손실 함수
- 참값과 예측값의 차이인 오차들의 제곱 평균으로 정의
- 제곱을 해주기 때문에 이상치(outlier)에 민감

  ![MSE](https://media.vlpt.us/images/changhtun1/post/e2f84c43-a9db-4e98-bef9-b3bd87932ca2/4.png)

2. MAE(Mean Absolute Error)

- 참값과 예측값의 차이인 오차들의 절대값 평균
- MSE보다 이상치에 덜 민감

![MAE](https://media.vlpt.us/images/changhtun1/post/43d7ffdf-bd62-4b18-a2d8-7329a4d5015e/5.png)

3. RMSE(Root Mean Squared Error)

- MSE에 루트를 취해준 것
- 참값과 비슷한 값으로 변환하기 때문에 해석이 쉬워짐

![RMSE](https://media.vlpt.us/images/changhtun1/post/8b234e87-ff6e-4744-9764-0181736f62ab/6.png)

-> 보통 Quadratic(2차 곡선형태) 형태의 미분 편의성이 좋기 때문에 회귀 모형의 비용함수로 `MSE`를 많이 사용
