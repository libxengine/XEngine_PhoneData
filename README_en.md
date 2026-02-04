[中文](README.md) ||  [English](README.en.md)  
# phonedata
Phone number location database.

## Description
Aiming to build the world's largest and most comprehensive phone number database.

## Features
1. Supports domestic IoT and virtual numbers.
2. Supports mobile and landline numbers.
3. Supports international numbers (Planned).
4. Supports location information.
5. Supports China Broadnet, Mobile, Unicom, and Telecom numbers.
6. Supports satellite numbers.
7. Supports carrier identification.
8. Supports Mobile Number Portability (MNP).

## Database Last Updated
2025.04.14

#### Number of Index Entries
517259

## Data Format
The protocol headers can be found at: https://github.com/libxengine/libxengine/blob/master/XEngine_Include/XEngine_ProtocolHdr.h. The parent project is: https://github.com/libxengine/libxengine.  
The phone number data format consists of four partitions: Header Partition, Operator Partition, Location Partition, and Number Partition. Each partition is preceded by an XENGINE_PROTOCOLHDR protocol header.  
You can use the protocol header to verify the data format. The wHeader and wTail fields verify if it follows the standard protocol.  
unOperatorType and unOperatorCode verify the protocol type, wCrypto verifies if the subsequent content is encrypted, and unPacketSize provides the data size.  

#### Header Partition
XENGINE_PROTOCOLHDR + Version number. A 30-byte header + 8-byte version, totaling a 38-byte partition header. The specific format is as follows:  
XENGINE_PROTOCOLHDR + 20240622

#### Operator Partition
XENGINE_PROTOCOLHDR + Type-OperatorName, ..., separated by spaces and mapped via the - symbol. The wPacketSerial of the protocol header is set to the count of the mapping list.  
XENGINE_PROTOCOLHDR + 0-UNKNOWN 1-CMCC 2-CUCC... etc. For example, 0 represents Unknown, 1 represents CMCC (China Mobile).

#### Location Partition
XENGINE_PROTOCOLHDR + Province-City-AreaCode. 30-byte header followed by variable-sized content. The size of the subsequent content is determined by the payload size in the header. Specific format:  
XENGINE_PROTOCOLHDR + 028-Sichuan-Chengdu

#### Number Partition
The payload size in XENGINE_PROTOCOLHDR represents the number of index entries, not the subsequent payload size. The size of the index data is variable, with each index separated by \n.  
Specific format: Number, Area Code, Number Type, Ported Status (if ported, followed by -Original Network Type), as follows:  
XENGINE_PROTOCOLHDR + 1994088-028-2-0. For example, if it is Unicom ported to SMS: 1994088-028-2-0-1.

## How to Contribute
There are two ways to submit and merge new phone numbers. However, for both methods, you must fill in the information according to the following format:  
Index - Phone Number - Operator - Province - City - Area Code - MNP Status (Set to 0 if not ported, otherwise set to the original operator type code).  
1, 199408840, China Telecom, Sichuan, Chengdu, 028, 0  
Follow the format above, separated by commas, one per line. The index should auto-increment. If you are unsure of certain details, you can fill it out as follows:  
1, 199408840, x, x, x, x, x (This signifies unknown information).

#### Using Issues
If you prefer a simple and convenient method, you can submit new phone numbers to us by opening an Issue.  
Create a new issue in the issue list and write the phone numbers you want to add. You may omit the index, for example:  
199408840, China Telecom, Sichuan, Chengdu, 0  

#### Using Pull Requests (PR)
Merging via PR is the recommended method. This way, you can actively contribute, and your name will be displayed in the contributors list.  
Write the data according to the requirements above. For example, if you want to merge a China Telecom number, add it to CTCC.txt:  
1, 199408840, China Telecom, Sichuan, Chengdu, 028, 0  
You need to write the phone number into the designated file within the Phone folder, categorized by operator:  
| Operator (EN)| Operator (CN) |
| -------- | --------- |
| CMCC     | 中国移动   |
| CUCC     | 中国联通   |
| CTCC     | 中国电信   |
| CRTG     | 中国广电   |
| CTCC_V   | 电信虚拟   |
| CUCC_V   | 联通虚拟   |
| CMCC_V   | 移动虚拟   |
| CTCC_I   | 电信座机   |
| CUCC_I   | 联通座机   |
| CMCC_I   | 移动座机   |
| SATE     | 卫星通信   |
| IOT      | 物联网     |

###### Contribution Steps
Fork this repository.   
Create a new Feat_xxx branch.  
Commit your code  
Create a new Pull Request.  

## Code Structure
 - Data     Database files.
 - Phone    Folder for submission records.
 - Source   示Example folder.例文件夹
 - XEngine_PhoneNumber Original data conversion program.

#### Example Code

| Status  | Language | Description                  | Contributor               |
|:-----    | :----    |:---------------------|:--------------------|
| Pending    | [golang](XEngine_APPExample/golang)         | golang query client implementation        | TBD |
| Pending    | [php](XEngine_APPExample/php)               | php query client implementation           | TBD |
| Pending    | [java](XEngine_APPExample/java)             | java query client implementation          | TBD |
| Pending    | [lua](XEngine_APPExample/lua)               | 纯 lua query client implementation        | TBD |
| Completed  | [c/c++](XEngine_APPExample/C/)              |  c/c++ query client implementation        | [xengine](https://github.com/libxengine) |
| Pending    | [rust](XEngine_APPExample/rust)             | rust query client implementation          | TBD |
| Pending    | [python](XEngine_APPExample/python)         | python query client implementation        | TBD |
| Pending    | [nodejs](XEngine_APPExample/nodejs)         | nodejs query client implementation        | TBD |
| Pending    | [csharp](XEngine_APPExample/csharp)         | csharp query client implementation        | TBD |
| Pending    | [erlang](XEngine_APPExample/erlang)         | erlang query client implementation        | TBD |
| Pending    | [php_ext](XEngine_APPExample/php7_ext)      | php c 扩展 xdb query client implementation | TBD |
| Pending    | [nginx](XEngine_APPExample/nginx)           | nginx 扩展 xdb query client implementation | TBD |

## Disclaimer
This database is for educational and research purposes only. It must not be used for any commercial or illegal purposes. Otherwise, the user shall bear all consequences.  
This database originates from the internet, and the copyright belongs to the original authors. I am merely organizing the data. If there is any infringement, please inform me, and it will be deleted.