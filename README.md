# almost-prime

$k, n$について$n$未満の$k$-概素数を列挙する。almprm*.cppがアルゴリズムのメイン、数字の部分はバージョン。

## 概素数とは

任意の非負整数$k$に対して$k$-概素数($k$-almost prime)は素因数の個数がちょうど$k$個であるような自然数の集合と定義される。
$k = 0$であるとき$k$-概素数の要素は1のみ、$k=1$のときは素数の集合に一致、$k = 2$のとき半素数の集合に一致する。

# BUILD

```
mkdir build && cd build
cmake -S ../
cmake --build ./
```

# USAGE

```
./almprm.exe k n -ver
```

$n$未満の$k$-概素数を5回列挙し、かかった時間の平均を出力。-verでバージョンを指定。almprm2_2.cppに対応するバージョンを使用したい場合は

```
./almprm.exe k n -2_2
```
という風に入力する。

-verを指定しなかった場合は最新バージョンが使われる。

------------------------------------------

## almprm1.cpp

激遅。オーダーは$O(n^2)$ぐらいだと思われる。話にならない。素数列挙における試し割り法の拡張とみなせる。

## almprm2_*.cpp

$PF[i]$が$i$の素因数の個数を表すような配列$PF$を作成する方法。素数列挙におけるエラトステネスの篩の拡張とみなせる。

## almprm3_*.cpp

$k$個の素数の積のパターンを全通り作るというごり押しな方法。全通り作るのよりもその後作ったのを昇順にソートする方が時間かかるし大変。

## sieve.cpp

素数配列の作成、方法はエラトステネスの篩。

## merge.cpp

ソートされた複数個の配列をまとめてmergeする。「複数個の配列」の置き方によって複数種類の関数を用意してある。