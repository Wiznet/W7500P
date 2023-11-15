/*******************************************************************************************************************************************************
 * Copyright ⓒ 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
#ioLibrary Driver
The ioLibrary means “Internet Offload Library” for WIZnet chip. It includes drivers and application protocols. 
The driver (ioLibrary) can be used for [W5500](http://wizwiki.net/wiki/doku.php?id=products:w5500:start) application designs. These will be updated continuously.

##ioLibrary
This driver provides the Berkeley Socket type APIs.
- Directory Structure
<!-- ioLibrary pic -->
![ioLibrary](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w5500:iolibrary_bsd.jpg "ioLibrary")

- Ethernet : SOCKET APIs like BSD & WIZCHIP([W5500](http://wizwiki.net/wiki/doku.php?id=products:w5500:start), W5200 and etc) Driver
- Internet :
  - DHCP client
  - DNS client
  - Others will be added.

## Revision History
Last release : Nov. 2014
