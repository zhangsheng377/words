#  单词路径
###  算法思路：
	1.先从系统的words文件中读取所有单词，然后对其进行统一小写化和去重处理，减小问题规模;
	2.若所取的单词与目标单词长度不一致，则直接输出"Can't find.";
	3.若一致，则查找该单词与目标单词同一位置上不一样的字母位置，依次对这些位置查找与该单词相近的单词，类似正则表达式d?g ;
	4.然后对相近的单词进行去环处理，即过滤掉在已经过节点中的单词;
	5.接下来依次对这些相近单词执行到目标单词的递归搜索;
	6.并利用已有的最优路径长度进行剪枝。
###  编译方法：
	一开始准备用boost中的正则表达式库，但后来发现自己写的匹配搜索也可以完成任务，于是就没用boost。这样一来，该项目就变成了单文件项目，极好编译：
	1.下载并安装 codeblocks，双击 wordsapp.cbp 可打开项目，点击编译按钮即可;
	2.也可以在命令行中执行 g++ -Wall -O2 main.cpp -o wordsapp ，即可生成可执行文件wordsapp，注意要将存有单词的words文件放在可执行文件wordsapp同一目录下，执行 ./wordsapp ，即可运行。
###  测试用例：
	1.依次输入： dig 和 dog ，输出： dig-->dog ;接着输入 y 即可开始下一轮搜索;
	2.依次输入： voise 和 noise ，输出：
	voise-->boise-->noise
	voise-->noise ;由于怕某些算例耗时太久，故把中间过程也输出;
	3.依次输入： cat 和 dog ，可看到许多次优解，耐心等待十几秒，即可看到最优解： cat-->cot-->dot-->dog
###  复杂度估计：
	由于用的是深度搜索，深度是单词对应位置上不同字母的个数，故可把深度看作常数;每一层的宽度是该单词的相近单词个数，故宽度也可看作常数;但每次搜索相近单词需要遍历全部words，故复杂度为O(n^c)。
###  bug：
	1.由于是查找该单词与目标单词同一位置上不一样的字母的位置，但在极端情况下可能要变已经一样的位置，但该极端情况较少且未经验证，若搜索全部位置耗时太久，故保留此bug，解决方法见 预备更新的算法 部分。
###  预备更新的算法：
	1.在现有的基础上，找到一个合适的算法来预估单词与目标单词的距离，以此来对相近单词进行排序，即可大幅加快搜索速度;
	2.彻底把每个单词看作一个节点，在该单词与其每个相近单词节点之间建立变更第几位的双向链路，即可使用最短路径算法来搜索;该方案在单词量大时，建立链路的处理需要很长时间;但可以将处理完后的数据结构保存到文件，下次直接读取即可。