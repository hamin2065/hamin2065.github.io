---
layout: post
title: Firebase
color: rgb(242,85,44)
tags: [Firebase]
---



# Firebase란?
![coding](../../../assets/img/posts/firebase_1.jpg)
- 14년도에 구글에서 인수한 모바일, 웹 애플리케이션 개발 플랫폼
- 백엔드 기능을 클라우드 서비스 형태로 제공해서 서버리스 애플리케이션 개발이 가능

# Firebase의 개발 기능 제공

## 1. Authentication(인증)
![coding](../../../assets/img/posts/firebase_2.jpg)
: Firebase 인증은 앱에서 사용자 인증 시 필요한 백엔드 서비스와 사용하기 쉬운 SDK, 기성 UI 라이브러리를 제공한다. 비밀번호, 전화번호, 인기 ID 제공업체(예: Google, Facebook, Twitter 등)를 통한 인증이 지원된다.

Firebase 앱에 대한 사용자 로그인을 처리할 때는 __FirebaseUI를__ 완전 삽입형 인증 솔루션으로 사용하는 방법도 있고 __Firebase 인증 SDK를__ 사용해 하나 이상의 로그인 방법을 앱에 통합하는 방법도 있다.

### Firebase UI 인증
: 삽입형 인증 솔루션

전체 로그인 시스템을 추가할 때 권장하는 방법

### Firebase SDK 인증
- 이메일 및 비밀번호 기반 인증
    : 이메일 주소와 비밀번호로 사용자를 인증, 비밀번호 재설정 이메일 전송도 처리
- ID 공급업체 통합
    : 제휴 ID 공급 업체와 통합하여 사용자를 인증(Google, Facebook, Twitter, Github 계정으로 로그인할 수 있는 수단을 제공)
- 전화번호 인증
    : 휴대전화로 SMS 메시지를 보내 사용자를 인증
- 커스텀 인증 시스템 통합
    : 기존 로그인 시스템을 Firebase 인증 SDK에 연결하면 Firebase 실시간 데이터베이스와 기타 Firebase 서비스를 이용가능
- 익명 인증
    : 임시 익명 계정을 생성하여 사용자들이 로그인하지 않고도 인증할 수 있는 기능 사용 가능. 사용자가 나중에 가입하면 익명 계정을 일반 계정으로 업그레이드 가능.


## 2. Firestore Database
![coding](../../../assets/img/posts/firebase_3.jpg)
: Firebase 및 Google Cloud의 모바일, 웹, 서버 개발에 사용되는 유연하고 확장가능한 데이터베이스이다. Firebase 실시간 데이터베이스와 마찬가지로 실시간 리스너를 통해 클라이언트 애플리케이션 간에 데이터의 동기화를 유지하고 모바일 및 웹에 대한 오프라인 지원을 제공해서 네트워크 지연 시간이나 인터넷 연결에 상관없이 원활하게 반응하는 앱을 개발할 수 있다. Cloud Firestore는 Cloud Functions를 비롯한 다른 Firebase 및 Google Cloud 제품과도 원활하게 통합된다.

### 주요기능
- __표현형 쿼리__ : 쿼리를 사용해 개별 문서를 가져오거나 쿼리 매개변수와 일치하는 컬렉션의 모든 문서를 가져올 수 있다.
- __실시간 업데이트__ : 실시간 데이터베이스와 마찬가지로 Cloud Firestore는 데이터 동기화를 사용해 연결된 모든 기기의 데이터를 업데이트한다.
- __오프라인 지원__ : Cloud Firestore는 앱에서 많이 사용되는 데이터를 캐시하기 때문에 기기가 오프라인 상태더라도 앱에서 데이터를 쓰고 읽고 수신 대기하고 쿼리할 수 있다. 기기가 올라인 상태로 전환되면 Cloud Firestore 에서 모든 로컬 변경사항을 다시 Cloud Firestore로 동기화한다.
- __확장형 설계__ : Cloud Firestore에서는 자동 멀티 리전 데이터 복제, 강력한 일관성 보장, 원자적 일괄 작업, 실제 트랜잭션 지원 등 Google Cloud의 강력한 인프라를 최대한 활용한다. Cloud Firestore는 세계 최대 규모의 앱에서 수많은 데이터베이스 워크로드를 처리하도록 설계되었다.

## 3. Storage
![coding](../../../assets/img/posts/firebase_4.jpg)

: Firebase용 Cloud Storage는 사진, 동영상 등의 사용자 제작 콘텐츠를 저장하고 제공해야하는 앱 개발자를 위해 만들어졌다.

Firebase용 Cloud Storage는 Google의 규모를 활용한 강력하고 단순하며 경제적인 객체 저장소 서비스이다. Cloud Storage용 Firebase SDK는 네트워크 품질과 관계없이 Firebase 앱의 파일 업로드 및 다운로드에 Google 보안을 적용한다.

이 SDK를 사용하여 이미지, 오디오, 동영상 등의 사용자 제작 콘텐츠를 저장할 수 있다. 서버에서는 Google Cloud Storage API를 사용하여 동일한 파일에 액세스할 수 있다.

### 주요 기능
- __견고한 작업__ : Firebase SDK는 네트워크 품질에 관계없이 업로드 및 다운로드를 실행한다. 업로드 및 다운로드가 중지된 위치부터 다시 시작되므로 사용자의 시간과 대역폭이 절약된다.
- __강력한 보안__ : 선언적 보안 모델을 사용하여 파일 이름, 크기, 콘텐츠 유형 및 기타 메타데이터를 기준으로 액세스를 허용할 수 있다.
- __높은 확장성__ : Cloud Storage는 앱 사용자가 급증할 때 엑사바이트급 규모로 확장이 가능하도록 설계되었다.

참고 사이트

https://firebase.google.com/docs?authuser=0

https://nomadcoders.co/nwitter/lobby 