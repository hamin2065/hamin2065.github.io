---
layout: post
title:  "React Hooks #1.useState"
subtitle:   
categories:  Web
tags: react
---

실습 방법 : 
[Code SandBox]
https://codesandbox.io/?from-app=1 에서 로그인을 하고 react를 선택해서 새 프로젝트를 열어준다.

# useState

```javascript
import React, { useState } from 'react';//1번째 줄

function Example(){
  const [count, setCount] = useState(0);//4번째 줄

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onclick={() => setCount(Count + 1)}>//9번째 줄
      Click me
      </button>
    </div>
  );
}
```
- 1번째 줄 : `useState` Hook을 React에서 가져온다.
- 4번째 줄 : `useState` Hook을 이용하면 __state 변수와__ __해당 state를 갱신할 수 있는 함수가__ 만들어진다. 또한 `useState`의 인자의 값으로 `0`을 넘겨주면 `count` 값을 0으로 초기화할 수 있다.
- 9번째 줄 : 사용자가 버튼 클릭을 하면 `setCount` 함수를 호출하여 state 변수를 갱신한다. React는 새로운 count 변수를 Example 컴포넌트에 넘기며 해당 컴포넌트를 리렌더링한다.  

- - -
# useInput


원래 state를 쓰고싶으면 class를 선언해주어야 했는데 Hooks가 있어서 state를 함수에도 쓸 수 있게 되었다.
class를 쓸 때는 render이나 this와 같은 문법이 필요하기 때문에 복잡하지만 hooks를 쓰면 그런 문법들은 필요가 없다.

```javascript
import React, { useState } from "react";

import "./styles.css";
//validator : 특정문자를 쓸 수 없도록
const useInput = (initialValue, validator) => {
  const [value, setValue] = useState(initialValue);
  const onChange = (event) => {
    const {
      target: { value }
    } = event;

    let willUpdate = true;
    //validator의 타입이 함수라면 willUpdate에 value값을 업데이트
    if (typeof validator === "function") {
      willUpdate = validator(value);
    }
    if (willUpdate) {
      setValue(value); //willUpdate는 항상 true이기 때문에 항상 업데이트가 될 것이다.
    }
  };
  return { value, onChange };
};

export default function App() {
  //maxLen에 value값을 받아서 value.length값을 검사
  const maxLen = (value) => value.length <= 10;
  const name = useInput("Mr.", maxLen);
  return (
    <div className="App">
      <h1>Hello</h1>
      <input placeholder="Name" {...name} />
    </div>
  );
}
//value = {name.value} onChange = {name.onChange} 합쳐서 {...name}이라고 쓴다.

/*
name을 사용해서 useInput에 "Mr."과 maxLen을 넣어준다.
validator가 바뀌면서 typeof validator을 검사하고 이 타입이 function이라면 willUpdate에 validator의 결과를 업로드한다.
여기서 validator은 maxLen이고 결과는 True또는 False이다.
value의 길이가 10보다 작으면 결과는 True이고 그렇지 않으면 False이다.
True인 경우에는 setValue(value)를 통해서 업데이트를 시킨다.
*/
```
- - -

# useTabs

```javascript
import React, { useState } from "react";

//불러올 content
const content = [
  {
    tab: "Section 1",
    content: "I'm the content of the Section 1"
  },
  {
    tab: "Section 2",
    content: "I'm the content of the Section 2"
  }
];

const useTabs = (initialTab, allTabs) => {
  //allTabs가 아니거나 allTabs가 배열이 아닌경우는 종료시킨다.
  if (!allTabs || !Array.isArray(allTabs)) {
    return;
  }
  const [currentIndex, setCurrentIndex] = useState(initialTab);
  return {
    currentItem: allTabs[currentIndex],
    changeItem: setCurrentIndex

  };
};

export default function App() {
  const { currentItem, changeItem } = useTabs(0, content);
  return (
    <div className="App">
      {content.map((section, index) => (

        <button onClick={() => changeItem(index)}>{section.tab}</button>
      ))}
      <div>{currentItem.content}</div>
    </div>
  );
}
//현재 내가 선택한 Section의 content만 보여주는것이 목표!
/*버튼을 클릭하면 changeItem에게 index를 전달시켜서 setCurrentIndex를 바꿔주고 이것은 state를 바꿔줄 것이다.(useState) 
그러면 currentItem의 currentIndex를 바꿔서 모든 것을 새로고침한다.*/
```