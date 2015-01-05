#!/bin/bash

# ＜概要＞
# NNによる学習を実行し，
# 　1. 学習の様子（学習ステップ数毎の誤差推移図）や，
# 　2. 学習後の学習データに対する学習度合い，
# 　3. 学習に用いなかったテスト用データに対する評価，
# を行う（予定）．

# ＜使い方＞
# prompt> ./run_nn.bash $rand-seed

EXE=nn_num


# 学習ステップ数毎の誤差推移図作成
learning_fig() {
    datafile=`echo $STDOUT | sed s/txt/data/`
    figfile=`echo $STDOUT | sed s/txt/svg/`
    grep iteration $STDOUT | tr -s " " " " | cut -f3,6 -d" " > $datafile
    echo set xlabel \"iteration\" > .gnuplot
    echo set ylabel \"error\" >> .gnuplot
    echo set title \"Error transition per iteration on BP-NN\" >> .gnuplot
    echo set terminal svg >> .gnuplot
    echo set output \"$figfile\" >> .gnuplot
    echo plot \"$datafile\" with line >> .gnuplot
    gnuplot < .gnuplot
}

# 2. 学習後の学習データに対する学習度合い
learned_fig() {
    datafile=`echo $STDOUT | sed s/txt/learned/`
    grep CHECK $STDOUT | cut -f2- -d" " > $datafile
}


if [ -e $EXE -a $# -eq 1 ] ; then
    STDOUT=result-seed$1.txt
    ./$EXE $1 | tee $STDOUT
    learning_fig
    learned_fig
else
    echo " You must run \"make\" before use this script."
    echo " This script requires Random-Seed to run, such as
    ./run_nn.bash 1000"
    exit 1
fi
