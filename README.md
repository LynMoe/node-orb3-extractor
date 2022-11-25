# node-orb3-extractor

This is a Node.js wrapper for [ORB-SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3)'s ORBextractor class.

## Installation

```bash
npm install orb3-extractor
```

> Note: This package requires OpenCV 4 to be installed on your system. You can install it using [this guide](https://docs.opencv.org/4.6.0/d7/d9f/tutorial_linux_install.html). 
> The package will look for the OpenCV libraries in the following paths:
>
> - `/usr/local/lib`
> - `/usr/lib`
>
> as well as the following include paths:
>
> - `/usr/local/include`
> - `/usr/include`
>
> If you have installed OpenCV in a different location, you can set the `OPENCV_LIB_DIR` and `OPENCV_INCLUDE_DIR` environment variables to point to the correct locations.

## Usage

```js
const orb3 = require('orb3')
const result = orb3.computeORB3('./image.jpg', {
  nFeatures: 1000,
  scaleFactor: 1.2,
  nLevels: 8,
  iniThFAST: 25,
  minThFAST: 6
})

console.log(result)
// {
//   keypoints: [
//     [x, y, size, angle, response, octave, class_id],
//     ...
//   ],
//   descriptors: [
//     [d1, d2, d3, ...],
//     ...
//   ]
// }
```

## API

### `orb3(imagePath, options) : { keypoints: number[][], descriptors: number[][] }`

Computes ORB3 descriptors for the given image.

#### `imagePath`

Type: `string`

Path to the image.

#### `options`

Type: `object`

##### `nFeatures`

Type: `number`\
Default: `1000`

The number of features to extract.

##### `scaleFactor`

Type: `number`\
Default: `1.2`

Scale factor between levels in the scale pyramid.

##### `nLevels`

Type: `number`\
Default: `8`

Number of levels in the scale pyramid.

##### `iniThFAST`

Type: `number`\
Default: `25`

FAST/AGAST detection threshold score.

##### `minThFAST`

Type: `number`\
Default: `6`

Minimum FAST/AGAST detection threshold score.

## License

MIT © [Lyn](https://lyn.moe)

## Acknowledgements

- [ORB-SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3)
