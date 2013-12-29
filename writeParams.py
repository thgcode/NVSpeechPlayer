﻿import codecs
from collections import OrderedDict
from pyklatt_ipa import _IPA_MAPPING as oldIpaData

oldIpaData['t']['formant-gain (2-6)']=(0,0,0,0,90)

data=OrderedDict()
for k in sorted(oldIpaData.keys()):
	v=oldIpaData[k]
	data[k]=item=OrderedDict()
	item['isNasal']=v['nasal']
	item['isStop']=v['stop']
	item['isLiquid']=v['liquid']
	item['isVowel']=v['vowel']
	item['isVoiced']=v['voice']
	item['voiceAmplitude']=1.0 if v['voice'] else 0 
	item['aspirationAmplitude']=0.75 if not v['voice'] and v['voicing-linear-gain']>0 else 0.0 
	item['cf1'],item['cf2'],item['cf3'],item['cf4'],item['cf5'],item['cf6']=[x*1.04 for x in v['freq (1-6)']]
	item['cf1']*=1.1
	item['cfNP']=v['freq-nasal-pole']
	item['cfN0']=v['freq-nasal-zero']
	item['cb1'],item['cb2'],item['cb3'],item['cb4'],item['cb5'],item['cb6']=[x*1.1 for x in v['bwidth (1-6)']]
	item['cbNP']=v['bwidth-nasal-pole']
	item['cbN0']=v['bwidth-nasal-zero']
	item['cb1']*=1.1
	item['ca1']=item['ca2']=item['ca3']=item['ca4']=item['ca5']=item['ca6']=1.0
	item['caNP']=1.0 if v['nasal'] else 0
	item['pf1'],item['pf2'],item['pf3'],item['pf4'],item['pf5'],item['pf6']=v['freq (1-6)']
	item['pb1'],item['pb2'],item['pb3'],item['pb4'],item['pb5'],item['pb6']=v['bwidth (1-6)']
	item['pa1']=0
	item['pa2'],item['pa3'],item['pa4'],item['pa5'],item['pa6']=(x/60.0 for x in v['formant-gain (2-6)'])
	item['parallelBypass']=v['formant-bypass-gain']/80.0
	if v['formant-parallel-gain']==0:
		item['fricationAmplitude']=0
	else:
		item['fricationAmplitude']=0.3 if v['voicing-linear-gain']>0 else 0.7 

data['h']=dict(copyAdjacent=True,isStop=False,isVoiced=False,voiceAmplitude=0,aspirationAmplitude=1)
data[u'ɪ']=data[u'I']
data[u'ɹ']['cf3']=1350

f=codecs.open('data.py','w','utf8')
f.write(u'{\n')
for k,v in data.iteritems():
	f.write(u'\tu\'%s\':{\n'%k)
	for k2,v2 in v.iteritems():
		f.write(u'\t\t\'%s\':'%k2)
		f.write(u'%s,\n'%v2)
	f.write(u'\t},\n')
f.write(u'}\n')
f.close()
