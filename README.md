# **markdown-cgi**
- This is a CGI module written in C for serving Markdown files.
---

## Features
- It can render markdown file to html style with C on the server side.

## Environment
| System | Software | Test |
| :----: | :----: | :----: |
| Windows 11 | IIS 10.0 | :white_check_mark: |
| Ubuntu 22.04 LTS | Apache 2.4.52 | :white_check_mark: |

## Usage
1. Download the source code
    ```
    curl https://www.axisflow.biz/pkg/markdown-cgi_0-2-0.zip -o markdown-cgi_0-2-0.zip
    ```
2. Decompress
3. Compile `markdown-cgi`
    - Windows
        ```shell
        gcc -o md-cgi.exe md-cgi.c md4c\md4c.c md4c\md4c-html.c md4c\entity.c
        ```
    - Linux
        ```shell
        gcc -o md-cgi md-cgi.c md4c/md4c.c md4c/md4c-html.c md4c/entity.c
        ```
4. Settings
    - IIS 10 on Windows
        1. Press **Win+R**, input `OptionalFeatures` and enter
        2. Ensure `Internet Information Services > World Wide Web Services > Application Development Features > CGI` selected
        3. Press **Win+R**, input `InetMgr` and enter
        4. Select an object(Host, Website, Directory or Application) from the tree
            > You can also add the following text in the tag **\<configuration\>** of the `web.config` file in the object path to skip steps 4~6(replace [] with yours):
            > ```xml
            > <system.webServer>
            >     <handlers accessPolicy="Read, Execute, Script">
            >         <add name="Markdown-Render" path="*.md" verb="*" modules="CgiModule" scriptProcessor="[Path\to\md-cgi.exe]" resourceType="File" requireAccess="None" />
            >     </handlers>
            > </system.webServer>
            > ```
        5. Double click **Handler Mappings** in the page
        6. Click *Add Script Map...* on the actions pane
            - Request path: Type `*.markdown *.mdown *.mkdn *.mkd *.mdwn *.md`
            - Executable: Choose `md-cgi.exe` just compiled
            - Name: Type `Markdown-CGI`
            - Request Restrictions: In *Mapping* tab, select **Invoke handler only if request is mapped to** and choose **File**
        7. Select your host from tree and double click **ISAPI and CGI Restrictions** in the page
        8. Click *Add...* on the actions pane
            - ISAPI or CGI path: Choose `md-cgi.exe` just compiled
            - Description: Type `Markdown-CGI`
            - Allow extension path to execute: :ballot_box_with_check:
    - Apache 2 on Linux(Ubuntu)
        > Assumed that your Apache was installed from `apt` command
        1. In the terminal, type `apachectl -M` to ensure *actions_module*, *cgi_module* and *cgid_module* enabled. If not, type the following commands:
            ```bash
            sudo a2enmod actions cgid
            ```
        2. Type `apachectl -t -D DUMP_INCLUDES` to ensure *conf-enabled/serve-cgi-bin.conf* included. If not, type the following commands:
            ```bash
            sudo a2enconf serve-cgi-bin.conf
            ```
        3. Open your site config(`/etc/apache2/sites-enabled/000-default.conf` default)
            ```
            Action markdown /cgi-bin/md-cgi
            AddHandler markdown .md
            ```
        4. Move `md-cgi` just compiled to `/usr/lib/cgi-bin/` 
5. Finished and you can try to open a markdown file throught your host by browsers

## Dependencies
- Use mity's MD4C 0.4.8 as Markdown-to-HTML converter gratefully.

## License
- `markdown-cgi` is covered with MIT license. Please see the file `LICENSE`.
- Some resources have different licenses. Please see the file `res/LICENSE`.