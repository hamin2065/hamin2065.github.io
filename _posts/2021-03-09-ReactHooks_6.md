---
layout: post
title:  "React Hooks #2.useEffect(useNotification, useAxios)"
subtitle:   
categories:  web
tags: react
---
# useNotification

Notification.permission
- denied : 사용자가 알람을 받는 것을 거부한다.
- granted : 사용자가 알람을 받는 것을 허용했다.
- default : 모든 알람이 허용되지 않는다. 사용자의 선택을 알 수 없어서 value가 denied인 것처럼 행동한다.

참고 : https://developer.mozilla.org/ko/docs/Web/API/notification 
```javascript
import React, { useState, useEffect, useRef, useCallback } from "react";
import ReactDOM from "react-dom";

const useNotification = (title, options) => {
  //윈도우에서의 알람이 아니면 종료시킨다.
  if (!("Notification" in window)) {
    return;
  }
  //알람이 허락되는 경우에만 알람이 가도록 만들어준다.
  const fireNotif = () => {
    if (Notification.permission !== "granted") {
      Notification.requestPermission().then((permission) => {
        if (permission === "granted") {
          new Notification(title, options);
        } else {
          return;
        }
      });
    } else {
      new Notification(title, options);
    }
  };
  return fireNotif;
};

export default function App() {
  const triggerNotif = useNotification("Can I?", { body: "Yes you can!" });
  return (
    <div className="App" style={{ height: "1000vh" }}>
      <button onClick={triggerNotif}>Hello</button>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
- - -
# useAxios

`App.js`
```javascript
import React, { useState, useEffect, useRef, useCallback } from "react";
import ReactDOM from "react-dom";
import useAxios from "./useAxios";

export default function App() {
  const { loading, data, error } = useAxios({
    url: "https://yts.mx/api/v2/list_movies.json"
  });
  console.log(
    `Loading: ${loading}\nError: ${error}\nData: ${JSON.stringify(data)}`
  );
  return (
    <div className="App" style={{ height: "1000vh" }}>
      <h1>hello</h1>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
`useAxios.js`
```javascript
import defaultAxios from "axios";
import { useEffect, useState } from "react";

const useAxios = (opts, axiosInstance = defaultAxios) => {
  const [state, setState] = useState({
    loading: true,
    error: null,
    data: null
  });
  if (!opts.url) {
    return;
  }
  useEffect(() => {
    axiosInstance(opts)
      .then((data) => {
        setState({
          ...state,
          loading: false,
          data
        });
      })
      .catch((error) => {
        setState({ ...state, loading: false, error });
      });
  }, []);
  return state;
};

export default useAxios;
```

refetching : useEffect를 다시하게 만든다. 

`App.js`
```javascript
import React, { useState, useEffect, useRef, useCallback } from "react";
import ReactDOM from "react-dom";
import useAxios from "./useAxios";

export default function App() {
  const { loading, data, refetch } = useAxios({
    url: "https://yts.mx/api/v2/list_movies.json"
  });

  return (
    <div className="App" style={{ height: "1000vh" }}>
      <h1>{data && data.status}</h1>
      <h2>{loading && "Loading"}</h2>
      <button onClick={refetch}>Refetch</button>
    </div>
  );
}

const rootElement = document.getElementById("root");
ReactDOM.render(<App />, rootElement);
```
`useAxios.js`
```javascript
import defaultAxios from "axios";
import { useEffect, useState } from "react";

const useAxios = (opts, axiosInstance = defaultAxios) => {
  const [state, setState] = useState({
    loading: true,
    error: null,
    data: null
  });
  const [trigger, setTrigger] = useState(0);
  if (!opts.url) {
    return;
  }
  const refetch = () => {
    setState({
      ...state,
      loading: true
    });
    //setTrigger을 통해서 숫자를 발생시킨다.
    setTrigger(Date.now());
  };
  useEffect(() => {
    axiosInstance(opts)
      .then((data) => {
        setState({
          ...state,
          loading: false,
          data
        });
      })
      .catch((error) => {
        setState({ ...state, loading: false, error });
      });
  }, [trigger]); //그 숫자를 통해서 trigger가 바뀌면 useEffect가 다시 실행될 것이다.
  return { ...state, refetch };
};

export default useAxios;
```