---
layout: post
title:  "React Hooks #2.useEffect(useTitle, useClick)"
subtitle:   
categories:  web
tags: react
---

# UseEffect

componentWillUnmount, componentDidMount, componentWillUpdate와 비슷하다.

```javascript
import React, { useEffect, useState } from "react";

import "./styles.css";

export default function App() {
  const sayHello = () => console.log("hello");
  useEffect(() => {
    sayHello();
  });
  const [number, setNumber] = useState(0);
  const [aNumber, setaNumber] = useState(0);
  return (
    <div className="App">
      <h1>Hi</h1>
      <button onClick={() => setNumber(number + 1)}>{number}</button>
      <button onClick={() => setaNumber(aNumber + 1)}>{aNumber}</button>
    </div>
  );
}
```
새로고침을 하면 콘솔에 `hello`가 출력된다 -> componentDidMount역할

버튼을 누르면 콘솔에 `hello`가 출력된다. -> componentDidUpdate역할

useEffect는 2개의 인자를 받는데 첫 번째는 function이고 두 번째는 배열형태이다.
```javascript
useEffect(sayHello, []);
```
```javascript
const [number, setNumber] = useState(0);
const [aNumber, setaNumber] = useState(0);
useEffect(sayHello, [number]);
```
: number의 버튼을 클릭할때마다 sayHello함수가 호출된다.
- - -
## useTitle

```javascript
import React, { useEffect, useState } from "react";

import "./styles.css";

const useTitle = (initialTitle) => {
  //initialTitle에 "Loading..."이 들어가고 title에도 들어감
  const [title, setTitle] = useState(initialTitle);
  const updateTitle = () => {
    const htmlTitle = document.querySelector("title");
    htmlTitle.innerText = title;
  };
  //useEffect가 mount되면 위의 htmlTitle이 "Loading..."이된다.
  useEffect(updateTitle, [title]);
  return setTitle;
};

export default function App() {
  //처음에 "Loading..."으로 초기화
  const titleUpdater = useTitle("Loading...");
  setTimeout(() => titleUpdater("Home"), 5000);
  return (
    <div className="App">
      <div>Hi</div>
    </div>
  );
}

 ```
 title이 바뀌면 titleUpdater가 바뀌면서 제목이 바뀌게 된다.
 - - -

# useClick

Reference : 우리의 component의 어떤 부분을 선택할 수 있는 방법
`document.getElementByID()`를 사용하는 것과 비슷하다.

react에 있는 모든 component는 reference element를 가지고 있다.

reference 연습 :
```javascript
export default function App() {
  const input = useRef();
  //5초 후에 박스에 블럭처리를 해준다.
  setTimeout(() => input.current.focus(), 5000);
  return (
    <div className="App">
      <h1>Hello</h1>
      <input ref={input} placeholder="la" />
    </div>
  );
};
```

`useClick.js`
```javascript
import React, { useState, useEffect, useRef } from "react";
import ReactDOM from "react-dom";

import "./styles.css";

const useClick = (onClick) => {
  if(typeof onClick !== "function"){
    return;
  }
  const element = useRef();
  useEffect(() => {
    if (element.current) {
      element.current.addEventListener("click", onClick);
    }
    //component가 mount되지 않았을 때 eventListener가 배치되지 않게 하기 위해 
    return () => {
      if(element.current){
        element.current.removeEventListener("click", onClick);
      }
    }; 
  }, []);
  return element;
};

export default function App() {
  const sayHello = () => console.log("say hello");
  const title = useClick(sayHello);
  //title에 접근권한을 준다.
  return (
    <div className="App">
      <h1 ref={title}>Hello</h1>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);

/* useClick을 이용해서 useRef()를 만들고 주어진 reference를 title에 주었다.
그리고 그 title을 h1태그에 ref속성으로 주어서 상호작용할 수 있도록 만들어준다.
여기서 useEffect의 할 일은 reference안에 element.current가 있는지 확인하는 것이다.
그리고 if문을 통해서 조건이 맞으면 Click이벤트를 부여하는 것이다.*/

```
useEffect에 있는 함수는 componentDidmount와 componentDidUpdate때 호출되는 것이다.([]안에 dependency가 없는 경우)
useEffect를 return 받은 그 함수는 componentWillUnMount일때 호출되는 것이다.

