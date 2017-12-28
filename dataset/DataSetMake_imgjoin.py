# -*- coding: utf-8 -*
from PIL import Image
import os
import argparse
import requests
from cStringIO import StringIO
import math
import json

parser = argparse.ArgumentParser(description='MyScript')

parser.add_argument('images_x_start', type=int)
parser.add_argument('images_x_end', type=int)
parser.add_argument('images_y_start', type=int)
parser.add_argument('images_y_end', type=int)
parser.add_argument('zoom_level', type=int)
parser.add_argument('--inputJson', default="./jsonSample.txt")
parser.add_argument('--outputPath', default="Data")

args = parser.parse_args()

TILE_SIZE = 256

with open(args.inputJson, 'r') as json_fp:
    json_dict = json.loads(json_fp.read(),'utf-8')
print (str(json_dict))
INPUT_URL = json_dict['inputURL']
TARGET_URL = json_dict['targetURL']

OUTPUT_PATH = os.path.join(os.getcwd(),args.outputPath)
if not os.path.isdir(OUTPUT_PATH):
    os.makedirs(OUTPUT_PATH)


kernel_size = 1
input_img_num = len(INPUT_URL)

image_size_x = TILE_SIZE * ((args.images_x_end - int(kernel_size / 2) + kernel_size - 1) - (args.images_x_start - int(kernel_size / 2)) + 1)
image_size_y = TILE_SIZE * ((args.images_y_end - int(kernel_size / 2) + kernel_size - 1) - (args.images_y_start - int(kernel_size / 2)) + 1)
input_img = []
input_img.append(Image.new('RGBA', (image_size_x, image_size_y), (0, 0, 0, 0)))
target_img = Image.new('RGBA', (image_size_x, image_size_y), (0, 0, 0, 0))

def tile2latlon(x, y, z):
    lon = (x / 2.0**z) * 360 - 180 # 経度（東経）
    mapy = (y / 2.0**z) * 2 * math.pi - math.pi
    lat = 2 * math.atan(math.e ** (- mapy)) * 180 / math.pi - 90 # 緯度（北緯）
    return [lon,lat]


def demtofloat(n):
    if n == 'e':
        return 0
    else:
        return float(n)

def getTile(req_target, i, j, zoom_level):
    input_img_p = Image.new('RGBA', (TILE_SIZE, TILE_SIZE), (0, 0, 0, 0))
    error_flg = 0

    if req_target['type'] == 'localTile':
        path_format = req_target['format']
        path_format = path_format.replace('{z}', str(zoom_level))
        path_format = path_format.replace('{x}', str(i))
        path_format = path_format.replace('{y}', str(j))
        input_image_path = os.path.join(req_target['path'], path_format)

        if os.path.isfile(input_image_path):
            input_img_p = Image.open(input_image_path)
            input_img_p = input_img_p.resize((TILE_SIZE, TILE_SIZE))
        else:
            print("Can't get tile : %d - %d - %d" % (zoom_level, i, j))
            error_flg = 1
            return input_img_p, error_flg

    else:
        if req_target['type'] == 'tile':
            url_format = req_target['format']
            url_format = url_format.replace('{z}', str(zoom_level))
            url_format = url_format.replace('{x}', str(i))
            url_format = url_format.replace('{y}', str(j))
            input_image_url = req_target['url'] + url_format

        elif req_target['type'] == 'wms':
            start_point = tile2latlon(i, j, zoom_level)
            end_point = tile2latlon(i + 1, j + 1, zoom_level)
            url_format = req_target['format']
            url_format = url_format.replace('{minx}', str(end_point[1]))
            url_format = url_format.replace('{miny}', str(start_point[0]))
            url_format = url_format.replace('{maxx}', str(start_point[1]))
            url_format = url_format.replace('{maxy}', str(end_point[0]))
            url_format = url_format.replace('{maxy}', str(end_point[0]))
            url_format = url_format.replace('{output_width}', str(TILE_SIZE))
            url_format = url_format.replace('{output_height}', str(TILE_SIZE))
            input_image_url = req_target['url'] + url_format

        print 'input : ' + input_image_url

        res = requests.get(input_image_url, verify=False)

        if res.status_code == 200:
            content_type = res.headers["content-type"]
            if 'image' not in content_type:
                print("Not image URL : %d - %d - %d" % (zoom_level, i, j))
                error_flg = 1
                return input_img_p, error_flg

            resfile = StringIO(res.content)
            input_img_p = Image.open(resfile)
            input_img_p = input_img_p.resize((TILE_SIZE, TILE_SIZE))

        else:
            print("Can't get tile : %d - %d - %d" % (zoom_level, i, j))
            error_flg = 1
            return input_img_p, error_flg

    return input_img_p, error_flg


def dataset_make(images_x_start, images_x_end, images_y_start, images_y_end, zoom_level, imgs_num):
    dataset_size_x = TILE_SIZE * (images_x_end - images_x_start + 1)
    dataset_size_y = TILE_SIZE * (images_y_end - images_y_start + 1)

    dataset_input_img = []
    dataset_input_img.append(Image.new('RGBA', (dataset_size_x, dataset_size_y), (0, 0, 0, 0)))
    dataset_target_img = Image.new('RGBA', (dataset_size_x, dataset_size_y), (0, 0, 0, 0))

    error_flg = 0

    for i in range(images_x_start, images_x_end + 1):
        for j in range(images_y_start, images_y_end + 1):
            if not TARGET_URL == None:
                input_img_p, error_flg = getTile(TARGET_URL, i, j, zoom_level)
                if error_flg == 1:
                    print("Can't get tile : %d - %d - %d" % (zoom_level, i, j))
                    return dataset_input_img, dataset_target_img, error_flg
                else:
                    dataset_target_img.paste(input_img_p, ((i - images_x_start) * TILE_SIZE, (j - images_y_start) * TILE_SIZE))

            if not INPUT_URL[0] == None:
                input_img_p, error_flg = getTile(INPUT_URL[0], i, j, zoom_level)

                if error_flg == 1:
                    print("Can't get tile : %d - %d - %d" % (zoom_level, i, j))
                    return dataset_input_img, dataset_target_img, error_flg
                else:
                    dataset_input_img[0].paste(input_img_p, ((i - images_x_start) * TILE_SIZE, (j - images_y_start) * TILE_SIZE))

            print("Get tile : %d - %d - %d" % (zoom_level, i, j))

    if error_flg == 0:
        dataset_image = Image.new('RGBA', (dataset_size_x*2, dataset_size_y), (0, 0, 0, 0))
        dataset_image.paste(dataset_input_img[0], (0,0))
        dataset_image.paste(dataset_target_img, (dataset_size_x,0))
        dataset_image.save(os.path.join(OUTPUT_PATH,
                                        str(imgs_num) + '_' + str(images_x_start + int(kernel_size / 2)) + '_' +
                                        str(images_y_start + int(kernel_size / 2)) + '_'  + str(zoom_level) + '.png'))

    return dataset_input_img, dataset_target_img, error_flg


imgs_num = 1
for i in range(args.images_x_start, args.images_x_end + 1):
    for j in range(args.images_y_start, args.images_y_end + 1):
        print "----- input : " + str(imgs_num) + " : " + str(args.zoom_level) + "-" + str(i) + "-" + str(j) + " -----"
        input_img_p, target_img_p, error_flg = dataset_make(i - int(kernel_size / 2), i - int(kernel_size / 2) + kernel_size - 1,
                                                                            j - int(kernel_size / 2), j - int(kernel_size / 2) + kernel_size - 1,
                                                                            args.zoom_level, imgs_num)

        input_img[0].paste(input_img_p[0], ((i - args.images_x_start) * TILE_SIZE, (j - args.images_y_start) * TILE_SIZE))
        target_img.paste(target_img_p, ((i - args.images_x_start) * TILE_SIZE, (j - args.images_y_start) * TILE_SIZE))
        if error_flg == 0:
            imgs_num += 1


input_img[0].save("input_image.png" )
target_img.save("target_image.png" )

print "Make Images : " + str(imgs_num - 1)






