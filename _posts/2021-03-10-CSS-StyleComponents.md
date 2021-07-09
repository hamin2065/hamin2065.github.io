---
layout: post
title:  "CSS Styled Components"
subtitle:   
categories:  web
tags: other
---

# Styled Component를 쓰기 전
`App.js`
```javascript
import React, {Component, Fragment} from 'react';
import "./App.css";

function App() {
  return (
    <Fragment>
      <button className="button button--success">Hello</button>
      <button className="button button--danger">Hello</button>
    </Fragment>
    
    
  );
}

export default App;
```
`App.css`
```css
.button{
    border-radius: 50px;
    padding:5px;
    min-width: 120px;
    color:white;
    font-weight:600;
    -webkit-appearance: none;
    cursor:pointer;
}

.button:active,
.button:focus{
    outline:none;
}

.button--success{
    background-color: #2ecc71;
}

.button--danger{
    background-color: #e74c3c;
}
```

# Styled Components
`npm install styled-components`를 통해서 style component를 설치해준다.

javascript코드 안에서 CSS를 쓸 수 있고, CSS가 있는 컴포넌트를 사용할 수 있다.
```javascript
import React, {Component, Fragment} from 'react';
import styled from "styled-components";

class App extends Component{
  render(){
    return(
      <Container>
        <Button>Hello</Button>
        <Button danger>Hello</Button>
      </Container>
    );
  }
}

const Container = styled.div`
  height:100vh;
  width:100%;
  background-color:pink;
`;

const Button = styled.button`
  border-radius: 50px;
  padding:5px;
  min-width: 120px;
  color:white;
  font-weight:600;
  -webkit-appearance: none;
  cursor:pointer;
  &:active,
  &:focus{
    outline:none;
  }
  background-color: ${props => props.danger ? "#e74c3c":"#2ecc71"}
`;


export default App;
```
이 전에는 두 개의 컴포넌트와 하나 이상의 파일과 다른 클래스명이 필요했지만 styled component를 쓰면 하나의 파일로 완성할 수 있다.

- - - 
위의 코드로는 페이지에 색깔이 채워지지 않은 마진이 생긴다. 

영상에서는 "styled-components"에서 {injectGlobal}을 import했지만 버전이 업데이트되면서 injectGlobal를 createGlobalStyle이 대체하게된다.

# Anchor

```javascript
<Anchor href="http://google.com">Go to google</Anchor>
```
을 통해서 구글 홈페이지로 연결되는 버튼을 새로 만든다.

영상에서는 `withComponent`와 `extend`를 통해서 Anchor의 디자인을 바꿔줬지만 버전이 업데이트되면서 더이상 쓰이지 않는다.
```javascript
const Anchor = Button.withComponent("a").extend`
  text-decoration: none;
`;
```
 : 더 이상 쓰일 수 없음

 대체하는 코드
 ```javascript
 const Anchor = styled(Button)`
  text-decoration: none;
`;
```
# placeholder

```javascript
import React, {Component} from 'react';
import styled, { createGlobalStyle } from "styled-components";

const GlobalStyle = createGlobalStyle`
body {
  padding: 0;
  margin: 0;
}
`;

const Input = styled.input.attrs({
  required: true
})`
  border-radius:5px;
`;

class App extends Component{
  render(){
    return(<Container>
      <Input placeholder="hello"/>
    </Container>);
  }
}

const Container = styled.div`
  height:100vh;
  width:100%;
  background-color:pink;
`;


export default App;
```
- - - 

# Mixins

여러 곳에 같은 속성을 쓰고 싶은 경우
```javascript
import styled, { createGlobalStyle, css } from "styled-components";

const awesomeCard = css`
  box-shadow: 0 4px 6px rgba(50, 50, 93, 0.11), 0 1px 3px rgba(0, 0, 0, 0.08);
  background-color: white;
  border-radius: 10px;
  padding: 20px;
`
```
awesomeCard를 정의해주고 
```javascript
const Container = styled.div`
  height:100vh;
  width:100%;
  ${awesomeCard};
  background-color:pink;
`;

const Input = styled.input.attrs({
  required: true
})`
  border: none;
  ${awesomeCard};
`;
```
awesomeCard를 넣고 싶은 곳에 넣는다.

# Theming

한 가지 색깔을 쓰다가 갑자기 그 색깔을 전부 뒤집어 엎어야 하는 경우가 발생할 수 있다.

src파일안에 theme.js라는 파일을 만들고 색깔에 관련해서 코드를 작성한다.
```javascript
const theme={
    mainColor: "#3498db",
    dangerColor:"#e74c3c",
    successColor: "#2ecc71"
};

export default theme;
```

`App.js`
```javascript
import React, {Component} from 'react';
import styled, { createGlobalStyle, ThemeProvider } from "styled-components";
import theme from "./theme";

const GlobalStyle = createGlobalStyle`
body {
  padding: 0;
  margin: 0;
}
`;


const Container = styled.div`
  height:100vh;
  width:100%;
  background-color:pink;
`;

const Card = styled.div`
  background-color:red;
`;

const Button = styled.button`
  border-radius: 30px;
  padding:25px 15px;
  background-color: ${props => props.theme.successColor};
`


class App extends Component{
  render(){
    return(
      <ThemeProvider theme={theme}>
        <Container>
          <Form />
        </Container>
      </ThemeProvider>
    );
  }
}


const Form = () => (<Card><Button>Hello</Button></Card>)

export default App;
```
버튼에 색깔을 적용하고 싶은데 `<Button>`은 `<Container>`, `<Form>`, `<Card>` 아래에 있는 요소이다. 하지만 가장 아래에 있는 요소더라도 `theme.js`에 있는 색깔을 적용시킬 수 있다.
```
 ${props => props.theme.successColor}
 ```