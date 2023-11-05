# Hexapawn
## 1. 내용
알파 베타 프루닝 기법을 이용하여 최대 최소 알고리즘을 최적화시킨 헥사폰 게임 구현 <br><br>
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/659e563e-8e8e-4f89-b7a7-b1eae6057637">
</p>
<br>

## 2. 구성 요소
1) 3x3 보드판
2) 검은색 폰x3
3) 흰색 폰x3
<br>

## 3. 기본 규칙
1) 위치 : 반대편 진영에 횡대 배열 (default)
2) 이동 : 앞, 옆
3) 공격 : 왼쪽 대각선 앞, 오른쪽 대각선 앞
<br>

## 4. 진행 규칙
### 1) 색깔 선택
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/fe902e1f-9b17-4443-904f-b327f2718734">
</p>
<br>

### 2) 턴 선택
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/b26113a8-141d-41f1-9d87-3c575ea08cb5">
</p>
<br>

### 3) 보드판 선택
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/da7c2575-6d6f-4241-bdb0-d68770fddaa4">
</p>
<br>

### 4) 게임 진행
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/50fd6099-71aa-4ff9-a1af-179eb57b1906">
</p>
<br>

### 5) 게임 종료
<p align="center">
 <img src = "https://github.com/KKGB/Hexapawn/assets/69628911/8cfb9a5c-78f9-4331-a245-88e73fe73edc">
</p>
<br>

## 5. 폴더 구성
> Hexapawn
> > Header
> > > Manager.h
> >
> > > gameTree.h
> >
> > > gameTreeNode.h
>
> > Source
> > > main.cpp
> >
> > > Manager.cpp
> >
> > > gameTree.cpp
> >
> > > gameTreeNode.cpp
