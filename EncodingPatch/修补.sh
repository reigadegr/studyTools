#!/bin/sh

for i in $(find $(dirname "$0") -name "*java"); do
    if [ ! -z "$(file $i | grep data | sed '/ASC/d' | sed '/UTF/d')" ]; then
            TIME="$(date "+%s%N")"
            [ ! -d "/dev/patch_dir" ] && mkdir -p "/dev/patch_dir"
            echo "$i 需要修补"
            chmod +x $(pwd)/GB2312ToUTF8
            cp -af $i $i.bak
            $(pwd)/GB2312ToUTF8 $i > "/dev/patch_dir/patch_file_$TIME" && cat "/dev/patch_dir/patch_file_$TIME" > $i && echo "修补完毕"
            if [ -z "$(grep "public" $i)" ]; then
                echo "$i存在问题"
                mv $i.bak $i
            fi
            rm $i.bak
    fi
done
