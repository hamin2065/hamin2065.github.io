---
layout: post
title: 2021-01-17-JavaScript
color: rgb(242,85,44)
tags: [JavaScript]
---

# JavaScript란?
객체 기반의 스크립트 프로그래밍 언어이다. 이 언어는 웹 브라우저 내에서 주로 사용하며 웹 페이지와 사용자의 상호작용을 주된 목적으로 하고 있다. 
- - -
# HTML과 JavaScript

## 1. script태그

`<script></script>`의 HTML태그를 통해서 자바스크립트가 실행이 된다는 것을 알려줘야 한다. 
>  - HTML : `1+1`
>         출력 : `1+1`
>  - JavaScript `document.write(1+1)`
>         출력 : `2`

## 2. 이벤트
`<input type = "button" value = "hi" onclick = "alert('hi')">`
: `hi`라는 버튼을 만들고 클릭했을 때, `hi`라는 경고창 표시

`<input type = "text" onchange = "alert('changed')">`
: 박스 안에 text를 입력받고 그것을 경고창으로 표시

`<input type = "text" onkeydown = "alert('key down!')">`
: 사용자가 키보드키를 눌렀을 때, `key down!`을 경고창으로 표시

->`onclick`, `onchange`, `onkeydown` 은 event로 사용자와 상호작용하는 코드를 만드는 것이 가능해진다. 

## 3. 콘솔창
 : 자바스크립트는 파일로 만들어서 사용할 수도 있지만 마우스 우클릭을 해서 `검사`를 누르고 콘솔창을 띄워서 그곳에서 입력을 할 수도 있다. 
 
 - - -
# JavaScript

## 문자와 숫자 형태의 자료형(Data type)

- 숫자(Numbers) : 숫자로 표현된 자료형
    - `+, -, *, / `의 산술 연산자가 중요하다.
- 문자열(String) : `""` 또는 `''`로 감싸서 표현되는 문자열 형태의 자료형
    - 예시 : `.indexOf('     ')` : 문자의 인덱스를 반환해준다.
             `.trim()` : 문자열의 공백을 없애준다.
             `.toUpperCase()` : 모든 문자를 대문자로 바꿔준다.

> `1+1`은 숫자이고 `"1+1"` 은 문자열이다.
> `1+1`을 출력하면 `2`가 나오고 `"1"+"1"`을 출력하면 `"11"`가 나온다.

- - -
## 변수와 대입 연산자

> `var x = 1;`
>`var`은 변수라는 뜻이고 `x`는 변수의 이름이다. `=`는 대입연산자이다. 
>
>: x라는 변수에 1이라는 값을 대입한다는 뜻이다. 

 `1 = 2;` 는 에러이다. -> 상수에는 상수를 대입할 수 없다.
- - -
## 제어할 태그 선택하기
```
<input type = "button" value = "A" onclick"
document.queryselector('body').style.backGroundColor = 'black';
document.queryselector('body').style.color = 'white';"
>
```
 : `A`라는 이름의 버튼을 만들고 그것을 누르면 `<body>`태그에 배경색은 검정색이고 글씨색은 하얀색인 style 속성이 들어가게 한다.
- - -
## 비교연산자 & boolean
```
<script>
    document.write(1===1) -> True 를 출력
    document.write(1===2) -> False 를 출력
    document.write(1<2) -> True를 출력
</script>
```
boolean : `True`와 `False`의 2개의 값을 갖는 데이터 타입
- - -
## 조건문
```
<script>
  document.write("1<br>");
  if(true){
    document.write("2<br>");
  } else {
    document.write("3<br>");
  }
  document.write("4<br>");
</script>
```
출력:

> 1
> 
> 2
> 
> 4

```
<script>
  document.write("1<br>");
  if(false){
    document.write("2<br>");
  } else {
    document.write("3<br>");
  }
  document.write("4<br>");
</script>
```

출력:

> 1
>
> 3
>
> 4

- - -
## 조건문의 활용

```
 <input id="night_day" type="button" value="night" onclick="
    if(document.querySelector('#night_day').value === 'night'){
      document.querySelector('body').style.backgroundColor = 'black';
      document.querySelector('body').style.color = 'white';
      document.querySelector('#night_day').value = 'day';
    } else {
      document.querySelector('body').style.backgroundColor = 'white';
      document.querySelector('body').style.color = 'black';
      document.querySelector('#night_day').value = 'night';
    }
  ">
  ```

  : `night`라는 버튼을 만들고 그것을 클릭했을 때, `if문`이 실행되면서 배경을 검정색, 글씨를 하얀색으로 바꾸고 버튼의 이름을 `day`로 바꾼다. 
  `day`로 만든 버튼을 다시 클릭하면 `else구문`이 실행이되면서 배경을 하얀색, 글씨를 검정색으로 바꾸고 버튼의 이름은 다시 `night`가 된다. 

  - 같은 버튼을 여러개 만드는 경우 여러개의 id를 지정해야한다는 문제가 생긴다. 이를 해결하기 위해서 `this`를 사용한다. 또한 중복되는 `document.querySelector('body')` 를 없애기 위해서 변수 `target`을 사용한다.
  ```
  <input type="button" value="night" onclick="
    var target = document.querySelector('body');
    if(this.value === 'night'){
      target.style.backgroundColor = 'black';
      target.style.color = 'white';
      this.value = 'day';
    } else {
      target.style.backgroundColor = 'white';
      target.style.color = 'black';
      this.value = 'night';
    }
  ">
  ```

- - -

  ## 배열
  
  `var arr = ["a", "b"];`는 arr라는 배열을 초기화 한것이다.

  1. 각 요소에 접근하는 방법

    document.write(arr[0]); -> a를 출력

    document.write(arr[1]); -> b를 출력

  2. 배열의 길이를 구하는 방법

    document.write(arr.length); -> 2를 출력

  3. 배열에 새로운 요소를 추가하는 방법

    arr.push('c');
    arr.push('d');
    -> c와 d 가 arr배열에 추가된다.
    var arr = ["a", "b", "c", "d"];

 - - -

 ## 반복문

 `while문`과 `for문`이 있다. 
 `while문`의 경우 괄호안의 조건이 `true`인 경우에 실행된다. 
 ```
 var i = 0;
 while(i<3){
    document.write('1');
    document.write('2');
    i = i + 1;
 }
 ```
 : 1과 2가 총 3번 반복해서 출력이 된다.
- - -

 ## 반복문과 배열의 예시

 ```
 var arr = ['a','b','c','d'];
 var i = 0;
 while(i<arr.length){
     document.write('<li>' + arr[i] + '</li>');
     i = i + 1;
 }
 ```
> 출력 :  
>    * a
>    * b
>    * c
>    * d

- - -

## 함수

: 입력과 출력으로 이루어졌다. 
코드의 반복이 필요한데 연속적인 반복이 아닌 경우에 어떻게 처리를 해야하는가? -> 함수를 이용한다.

```
function '함수이름'(){
    //코드
}
```

```
function two(){
    document.write('<li>2-1</li>');
    document.write('<li>2-2</li>');
}
document.write('<li>1</li>');
two();
document.write('<li>3</li>');
two();
```

> 출력:
> * 1
> * 2-1
> * 2-2
> * 3
> * 2-1
> * 2-2

- 매개변수와 인자

```
function sum(left, right){
    document.write(left+right+'<br>');
}
sum(2,3);
sum(3,4);
```

: 여기서 `left`와 `right`는 매개변수라고 부르고 sum함수를 호출할때 `2,3` `3,4`는 인자라고 부른다. 

출력:
>
> 5
>
> 7

- return
  : 결과값을 단순히 출력하는 것이 아니라 더 많은 작업을 수행해야 하는 경우 이용한다.

```
function sum2(left, right){
    return left+right;
}

document.write(sum2(2,3)+'<br>');
document.write('<div style="color:red">'+sum2(2,3)+'</div>');
document.write('<div style = "font-size:3rem";>+sum2(2,3)+'</div>');
```

- - -

## 객체

- 객체의 읽고 쓰기

``` 
var coworkers = {
  "programmer" : "A",
  "designer" : "B"
};
```

```
document.write("programmer : " + coworkers.programmer + "<br>");
document.write("designer : " + coworkers.designer + "<br>");
coworkers.bookkeeper = "duru";
document.write("bookkeeper : " + coworkers.bookkeeper + "<br>");
coworkers["data scientist"] = "C";
document.write("data scientist : " + coworkers["data scientist"] + "<br>");
```

- 객체와 반복문
 : data를 다 가져와야 하는 경우

```
for (var key in cowerkers){
  document.write(key + ' : ' + coworkers[key] + '<br>');
}
```

출력 : 
```
programmer : A
designer : B
bookkeeper : C
data scientist : D
```

- 객체프로퍼티와 메소드

```
coworkers.showAll = function(){
  for(var key in this){
    document.write(key + ' : ' + this[key] + '<br>');
  }
}
```
출력 : 

```
programmer : A
designer : B
bookkeeper : C
data scientist : D
showAll : function(){for(var key in this){document.write(key + ' : ' + this[key] + '<br>');}}
```
- - -

## 파일로 쪼개서 정리 정돈하기

- Javascript 파일을 다른 파일로 저장한 후에 HTML 파일에서 쓸 수 있다. 

`<script src = "Javascript_file_name.js"></script>`
- - -

## 라이브러리와 프레임워크

- 라이브러리 : 활용가능한 도구들의 집합
- 프레임워크 : 소프트웨어의 특정 문제를 해결하기 위해서 상호 협력하는 클래스와 인터페이스의 집합

> JavaScript의 라이브러리 : jQuery
> 
> ex) 구글에서 제공하는 jQuery
> `<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>`
> `$('a')` : 이 웹페이지의 모든 `a태그`를 `jQuery`로 제어하겠다. -> 반복문을 쓰지 않아도된다.

1번 코드 :
```
var Links = {
  setColor:function(color){
    var alist = document.querySelectorAll('a');
    var i = 0;
    while(i < alist.length){
      alist[i].style.color = color;
      i = i + 1;
    }
  }
}
```


2번 코드 : 
```
var Links = {
  setColor:function(color){
    %('a').css('color',color);
  }
}
```

1번 코드와 2번 코드는 동일한 코드이다.