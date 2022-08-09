# Change Log

> ## v0.3.0
>> ### New Features
>>> 1. Tables, Underlines, Task Lists and Auto Linking are supported.
>> ### Changes
>>> 1.  The title is now filename instead of the path of file.
>> ### Bug Fixed
>>> 1. [**Security**] On Apache, the title is always the path of `md-cgi`.
---
> ## v0.2.1
>> ### Changes
>>> 1. Turn the favicon base64 code into a file.
>>> 2. Delete similar codes and add a new function to print favicon, css, and javascript.
> ## v0.2.0
>> ### New Features
>>> 1. Customizable CSS styles in `md-cgi.css` (that must be saved in the same directory with `md-cgi`).
>>> 2. Customizable JavaScript in `md-cgi.js` (that must be saved in the same directory with `md-cgi`).
>>> 3. Default `md-cgi.css` makes the page centered and scroll smoothly when use anchors.
>>> 4. Default `md-cgi.js` makes the document able to automatically gernerate anchors and replace `:[emojiname]:` with emojis.
>> ### Changes
>>> 1. Delete trivial codes.
>>> 2. Add favicon that combines [Octicons-markdown.svg](https://upload.wikimedia.org/wikipedia/commons/5/51/Octicons-markdown.svg) and [CodiMD Logo](https://d33wubrfki0l68.cloudfront.net/5a26e2c8eafa7e50df52260b0f912f53a4c52efe/002dd/assets/images/tool-icons/codimd.png).
>>> 3. Change the title of the page to `path/to/filename`.
---
> ## v0.1.0 - Initial Release
>> ### New Features
>>> 1. Use mity's [MD4C](https://github.com/mity/md4c) 0.4.8 as Markdown-to-HTML converter gratefully.
>>> 2. Just print the output from `md_html()`.
>> 
>> ### Bugs Found
>>> 1. [**Security**] Generate garbled text(or regular but not exists in the file) after original document in some makedown files if it is served on IIS.