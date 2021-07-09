---
layout: post
title:  "React Hooks #2.useEffect(useNetwork, useScroll, useFullscreen)"
subtitle:   
categories:  web
tags: react
---
# useNetwork 
:navigator가 online또는 offline으로 바뀔 때 작동하게한다.

```javascript
import React, { useState, useEffect, useRef } from "react";
import ReactDOM from "react-dom";

import "./styles.css";

const useNetwork = (onChange) => {
  //navigator.onLine은 true또는 false(온라인인지 아닌지)
  const [status, setStatus] = useState(navigator.onLine);
  const handleChange = () => {
    if (typeof onChange === "function") {
      onChange(navigator.onLine);
    }
    setStatus(navigator.onLine);
  };
  useEffect(() => {
    window.addEventListener("online", handleChange);
    window.addEventListener("offline", handleChange);
    () => {
      window.removeEventListener("online", handleChange);
      window.removeEventListener("offline", handleChange);
    };
  }, []);
  return status;
};

export default function App() {
  const handleNetworkChange = (online) => {
    console.log(online ? "We just went online" : "We are offline");
  };
  const onLine = useNetwork();
  return (
    <div className="App">
      <h1>{onLine ? "Online" : "Offline"}</h1>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
- - -
# useScroll

```javascript
import React, { useState, useEffect, useRef } from "react";
import ReactDOM from "react-dom";

import "./styles.css";

//사용자가 스크롤을 사용할 때 지정한 무언가를 지나치면 실행

const useScroll = () => {

  //x:0, y:0으로 우선 초기화
  const [state, setState] = useState({
    x: 0,
    y: 0
  });
  const onScroll = (event) => {
    setState({ y: window.scrollY, x: window.scrollX });
  };
  useEffect(() => {
    //scroll할 때 onScroll이벤트가 실행되도록 지정
    window.addEventListener("scroll", onScroll);
    return () => window.removeEventListener("scroll", onscroll);
  }, []);
  return state;
};

export default function App() {
  const { y } = useScroll();
  return (
    <div className="App" style={{ height: "1000vh" }}>
      <h1 style={{ position: "fixed", color: y > 100 ? "red" : "blue" }}>
        Hello
      </h1>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
- - -
# useFullscreen
:전체 화면을 만들고 전체화면을 해제시키는 함수를 작성하고 버튼을 통해서 실행한다.
```javascript
import React, { useState, useEffect, useRef, useCallback } from "react";
import ReactDOM from "react-dom";

import "./styles.css";

const useFullscreen = (callback) => {
  const element = useRef();
  const runCb = (isFull) => {
    if (callback && typeof callback === "function") {
      callback(isFull);
    }
  };
  //full화면으로 만들어주는 함수
  const triggerFull = () => {
    if (element.current) {
      if (element.current.requestFullscreen) {//Chrome, Safari
        element.current.requestFullscreen();
      } else if (element.current.requestFullscreen) {//firefox
        element.current.mozRequestFullScreen();
      } else if (element.current.webkitRequestFullscreen) {//opera
        element.current.webkitRequestFullscreen();
      } else if (element.current.msRequestFullscreen) {//microsoft
        element.current.msRequestFullscreen();
      }
      runCb(true);
    }
  };

  //full화면을 취소시켜주는 함수
  const exitFull = () => {
    document.exitFullscreen();
    if (document.exitFullscreen) {//Chrome, Safari
      document.exitFullscreen();
    } else if (document.mozCancelFullScreen) {//firefox
      document.mozCancelFullScreen();
    } else if (document.webkitExitFullscreen) {//opera
      document.webkitExitFullscreen();
    } else if (document.msExitFullScreen) {//microsoft
      document.msExitFullScreen();
    }
    runCb(false);
  };
  return { element, triggerFull, exitFull };
};

export default function App() {
  const onFullS = (isFull) => {
    console.log(isFull ? "We are full" : "We are small");
  };
  const { element, triggerFull, exitFull } = useFullscreen(onFullS);
  return (
    <div className="App" style={{ height: "1000vh" }}>
      <div ref={element}>
        <img src="" />
        <button onClick={exitFull}>Exit fullscreen</button>
      </div>
      <button onClick={triggerFull}>Make fullscreen</button>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
