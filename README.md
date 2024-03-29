#  单词路径
###  算法思路：
	项目wordsdata：
	1.先从系统的words文件中读取所有单词，然后对其进行统一小写化和去重处理，减小问题规模;
	2.创建NODE类，建立每个单词之间的联系，即若变化一位即可到达就保存下对方的id
	3.将整个nodes保存到文件 wordsdata1 中。
	项目words：
	1.将wordsdata项目中生成的wordsdata1文件拷贝到本项目中，在程序里读取并重新建立整个nodes;
	2.要求输入起始单词和目标单词，若单词不在nodes内，则输出 Can't find this word. 
	3.若所取的单词与目标单词长度不一致，则直接输出"Can't find.";
	4.若一致，则查找该单词与目标单词同一位置上不一样的字母位置，依次对这些位置nodes当中该单词节点的相近单词，类似正则表达式d?g ;
	5.然后对相近的单词进行去环处理，即过滤掉在已经过节点中的单词;
	6.接下来依次对这些相近单词执行到目标单词的广度优先搜索;
	7.并利用已有的最优路径长度进行剪枝。
###  编译方法：
	项目wordsdata：
	一开始准备用boost中的正则表达式库，但后来发现自己写的匹配搜索也可以完成任务，于是就没用boost。这样一来，该项目就变成了单文件项目，极好编译：
	1.下载并安装 codeblocks，双击 words.cbp 可打开项目，点击编译按钮即可;
	2.也可以在命令行中执行 g++ -Wall -O2 main.cpp -o wordsdataapp ，即可生成可执行文件wordsdataapp，注意要将存有单词的words文件放在可执行文件wordsdataapp同一目录下，执行 ./wordsdataapp ，耐心等待，即可生成 wordsdata1 文件。
	项目words：
	1.下载并安装 codeblocks，双击 words.cbp 可打开项目，点击编译按钮即可;
	2.也可以在命令行中执行 g++ -Wall -O2 main.cpp -o wordsapp ，即可生成可执行文件wordsapp，注意要将存有单词的wordsdata1文件放在可执行文件wordsapp同一目录下，执行 ./wordsapp ，即可运行。
###  测试用例：
	1.依次输入： dig 和 dog ，输出： dig-->dog ;接着输入 y 即可开始下一轮搜索;
	2.依次输入： voise 和 noise ，输出：Can't find the word
	3.依次输入： cat 和 dog ，可看到许多次优解，耐心等待十几秒，即可看到最优解： cat-->cot-->dot-->dog ;由于怕某些算例耗时太久，故把中间过程也输出。
###  复杂度估计：
	由于用的是广度搜索，广度是单词对应位置上不同字母的个数，故可把广度看作常数;每一层的宽度是该单词的相近单词个数，故宽度也可看作常数;故总的复杂度应该是O(c)，但需要指出的是：由于我们把数据处理放到了另一个项目中完成，所以复杂度才变为常数级;另外，搜索的复杂度其实跟单词个数的规模无关，而是跟所选单词之间的关系有关。
###  预备更新的算法：
	1.在现有的基础上，找到一个合适的算法来预估单词与目标单词的距离，以此来对相近单词进行排序，即可大幅加快搜索速度。
