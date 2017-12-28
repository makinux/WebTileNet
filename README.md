# WebTileNet
このプログラムはタイル画像をデータセットとしてchainer版pix2pixで学習を行い、Cesium上にWebDNNを用いて変換したタイルを表示するものです。

なおこちら( <https://qiita.com/knok/items/45f4bbe3f0058eba27e6> )で公開されているソースコードをもとにプログラムを作成しました。

## データセット作成
### 動作環境
以下の環境で動作を確認しています。

OS：Ubuntu 14.04 64bit

ソフトウェア : python2.7.6

### インストール方法
1.実行に必要な各パッケージをインストールします。

	sudo pip install pillow requests

2.datasetディレクトリ内のソースコードを任意の場所に設置してください。


### データセット作成手順
#### 地図タイル取得先URLの設定

地図タイルを取得するURLをJSON形式で設定したファイルを作成します。作成例としてjsonSample.txtを同梱しているのでこちらを基に作成してください。

##### 教師データと入力データの設定

    {
     "targetURL": 教師データとなる地図タイルの取得先URL
    ,
     "inputURL": [
                   入力データとなる地図タイルの取得先URL
                 ]
    }


教師データと入力データそれぞれの地図タイル取得先を設定します。地図タイル取得先の設定については下記の『地図タイルの取得先』を参照してください。


##### 地図タイルの取得先
	{
	"url": 地図タイル取得先のベースURL ,
	 "type": 取得する地図タイルの種類 ,
	 "format": 取得する地図タイルの形式
	}

・"url"		地図タイルの取得先のベースURL

・"type"	取得する地図タイルの種類。タイル地図形式やWMTSは"tile"、WMSは"wms"になります。

・"format"	拡張子やタイル座標、WMTS やWMSのパラメータなどの設定。詳細については下記の各タイル取得設定例を参照してください。


###### タイル地図形式の地図タイル取得先設定例(国土地理院 全国最新写真（シームレス）)：
	{
	"url": "http://cyberjapandata.gsi.go.jp/xyz/seamlessphoto/",
	 "type": "tile",
	 "format": "{z}/{x}/{y}.jpg"
	}

タイル地図形式の"format"では主としてタイル座標と拡張子やWMTSのパラメータ等を設定します。取得先の形式に従って設定してください。

タイル座標については以下のように記述してください。

	{z} : ズームレベル、{x} : タイルのX座標、{y} : タイルのY座標



###### WMS形式の地図タイル取得先設定例(地震ハザードステーション 地すべり地形分布図WMSサービス)：
	{
	"url": "http://www.j-shis.bosai.go.jp/map/wms/landslide?",
	"type": "wms",
	"format": "SERVICE=WMS&VERSION=1.3.0&REQUEST=GetMap&BBOX={minx},{miny},{maxx},{maxy}&CRS=EPSG:4612&WIDTH={output_width}&HEIGHT={output_height}&LAYERS=L-V3-S300&FORMAT=image/png&TRANSPARENT=FALSE"
	}

WMS形式の"format"ではWMSのパラメータ設定を行ないます。

取得先の形式に従って設定してください。

WMSのパラメータの中で取得範囲指定を行なうBBOX、取得する画像のサイズを指定するWIDTH、HEIGHTについては以下のように記述してください。

	BBOX={minx},{miny},{maxx},{maxy}
	WIDTH={output_width}
	HEIGHT={output_height}


#### データセットを作成
指定範囲内の複数のタイルを読み込み、タイル単位で学習用データやテスト用データを作成します。

・実行例：

	python DataSetMake_imgjoin.py 7266 7295 3206 3229 13 --outputPath datasets/test/train --inputJson ./jsonSample.txt

・コマンドライン引数

	引数1	指定する範囲の始点となるタイルのx方向の位置
	引数2	指定する範囲の終点となるタイルのx方向の位置
	引数3	指定する範囲の始点となるタイルのy方向の位置
	引数4	指定する範囲の終点となるタイルのy方向の位置
	引数5	ズームレベル
	--inputJson	地図タイル取得先URLを設定したjson形式のファイルを指定します。デフォルトは"./jsonSample.txt"。
	--outputPath	データセットの出力先ディレクトリの指定。ディレクトリがない場合は自動生成します。デフォルトは"Data"。



・実行後、--outputPathで指定したディレクトリ内に`{通し番号}_{x座標}_{y座標}_{ズームレベル}.png`が取得したタイルの枚数分生成されます。

　また、プログラムを実行したディレクトリ内に取得したタイルを繋げた、`input_image{通し番号}.png、target_image{通し番号}.png`が生成されます。



## 学習、モデル変換
### 動作環境
以下の環境で動作を確認しています。

OS：Ubuntu 14.04 64bit

ソフトウェア : python3.6.3(pyenvを使用)

### インストール方法
1.pyenvをインストールしてpython3.6.3を使えるようにします。

	cd ~
	sudo apt-get install  -y git
	sudo apt-get install -y make gcc
	sudo apt-get install -y make build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev xz-utils

	git clone git://github.com/yyuu/pyenv.git ~/.pyenv
	git clone https://github.com/yyuu/pyenv-virtualenv.git ~/.pyenv/plugins/pyenv-virtualenv

	vim ~/.bashrc
	以下を追記します。
	#-----ここから-----
	export PYENV_ROOT=$HOME/.pyenv
	export PATH=$PYENV_ROOT/bin:$PATH
	eval "$(pyenv init -)"
	#-----ここまで-----

	source ~/.bashrc

	# インストール可能なバージョンを調べてpython3.6.3をインストールします
	pyenv install -l
	pyenv install 3.6.3
	# pythonの環境を確認してpython3.6.3があることを確認します
	pyenv versions

2.WebDNNをインストールします。

	cd ~
	git clone https://github.com/mil-tokyo/webdnn
	cd webdnn
	# pyenvでwebdnnディレクトリ内ではpython3.6.3を使うように設定します
	pyenv local 3.6.3
	python setup.py install
	sudo pip install chainer

3.EmscriptenとEigenをインストールします。

	cd ~
	# cmake 3.4.3以上が必要なのでない場合はインストールします
	# 古いバージョンがあれば消しておきます
	sudo apt remove cmake
	sudo apt-get install build-essential
	# 取得先を確認(https://cmake.org/download/)し、wgetで取得します
	wget https://cmake.org/files/v3.10/cmake-3.10.1.tar.gz
	tar xf cmake-3.10.1.tar.gz
	cd cmake-3.10.1
	./configure
	make
	sudo make install

	# Emscriptenをインストール
	cd ~
	git clone https://github.com/juj/emsdk.git
	cd emsdk
	./emsdk install sdk-incoming-64bit binaryen-master-64bit
	./emsdk activate sdk-incoming-64bit binaryen-master-64bit
	source ./emsdk_env.sh

	# Eigenをインストール
	cd ~
	wget http://bitbucket.org/eigen/eigen/get/3.3.3.tar.bz2
	tar jxf 3.3.3.tar.bz2
	export CPLUS_INCLUDE_PATH=$PWD/eigen-eigen-67e894c6cd8f

4.実行に必要な各パッケージをインストールします。

	cd ~/webdnn
	sudo pip install pillow requests

5.WebDNNディレクトリ内にworkspaceディレクトリを作成します。

	mkdir workspace

6.workspaceディレクトリ内にtrain_dumpディレクトリ内のソースコードを設置してください。


環境設定については次のWebDNNのドキュメントも参考にしてください。
→ <https://mil-tokyo.github.io/webdnn/docs/tutorial/setup.html>


### 学習
・実行例：

	python train_joined.py --gpu 0 --dataset ./datasets/test/train --out ./models --epoch 300 --snapshot_interval 2000 --display_interval 100

・コマンドライン引数

	--gpu		使用するGPUの番号。-1でCPUで学習。
	--dataset	学習用データセットがあるディレクトリ
	--out		学習モデルなどの出力先ディレクトリ
	--epoch		学習回数
	--snapshot_interval	学習モデルなどの出力間隔
	--display_interval	学習状況のコンソール出力の間隔

・学習中に--outで指定したディレクトリに--snapshot_intervalで指定した間隔で学習モデルやテスト画像が出力されます。

### モデル変換
chainerで学習したモデルをWebDNNのモデルに変換します。

・実行例：

	python dump_graph.py --out ./out --enc-npz models/enc_iter_10000.npz --dec-npz models/dec_iter_10000.npz

・コマンドライン引数

	--out	変換したモデルの出力先ディレクトリ
	--enc-npz	変換元のモデル(enc_iter_XXXX.npzの名前のモデルを指定)
	--dec-npz	変換元のモデル(dec_iter_XXXX.npzの名前のモデルを指定)


・--outで指定したディレクトリに変換後のモデルが出力されます。このプログラムではWebAssembly用とWebGPU用の2種類のモデルが出力されます。


## Cesiumで変換したタイルを表示する
### 動作環境
htmlディレクトリ内のファイルをhttpサーバーに設置してください。また、変換済みの学習モデルを使用する場合はhttpサーバー内に設置してください。

設置した場所のURL/index.htmlにアクセスするとページが表示されます。

デモは[こちら](https://makinux.github.io/WebTileNet/html/index.html)

### 操作方法
#### 学習モデルの読み込み
・Model Pathに変換済み学習モデルがあるURLを入力します。初期値として、同梱しているPNG標高タイルからCS立体図へ変換を行なう学習済みモデルへのパスが入力されています。(こちらのモデルは[シームレス標高サービス PNG標高タイル](https://gsj-seamless.jp/labs/elev/)、[CS立体図（5mDEMもあり）](http://kouapp.main.jp/csmap/japan/csjapan.html)を学習データとして使わせていただきました。)

・model loadボタンをクリックすると学習モデルが読み込まれます。

#### タイル画像の変換
・Input Tileにタイルの取得先URLを入力します

入力例(シームレス標高サービス PNG標高タイル)：

	https://gsj-seamless.jp/labs/elev/m/{z}/{y}/{x}.png

タイル座標については以下のように記述してください。

	{z} : ズームレベル、{x} : タイルのX座標、{y} : タイルのY座標
・変換する地図タイルの範囲を指定します。初期値として千葉県付近のタイル座標が入力されています。Tile range XにはタイルのX座標、Tile range YにはタイルのY座標、Tile Zにはタイルのズームレベルを入力してください。

・convertをクリックするとタイルの変換が開始されます。

・clearをクリックするとCesium上の変換済みタイルが消去されます。





