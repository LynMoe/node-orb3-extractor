const path = require("path")
const addon = require("../build/Release/module")

/**
 *
 * @param {String} imagePath Path to the image
 * @param {Object} options ORB3 parameters
 * @param {Number} [options.nFeatures] Number of features to extract
 * @param {Number} [options.scaleFactor] Scale factor between levels in the scale pyramid
 * @param {Number} [options.nLevels] Number of levels in the scale pyramid
 * @param {Number} [options.iniThFAST] Initial threshold for FAST
 * @param {Number} [options.minThFAST] Minimum threshold for FAST
 * @returns {Object} ORB3 features
 * @returns {Array<Array<Number>>} return.keypoints Array of keypoints
 * @returns {Array<Array<Number>>} return.descriptors Array of descriptors
 * @example
 * const orb3 = require('orb3')
 * const result = orb3('./image.jpg', {
 *   nFeatures: 1000,
 *   scaleFactor: 1.2,
 *   nLevels: 8,
 *   iniThFAST: 25,
 *   minThFAST: 6
 * })
 * 
 * console.log(result)
 * // {
 * //   keypoints: [
 * //     [x, y, size, angle, response, octave, class_id],
 * //     ...
 * //   ],
 * //   descriptors: [
 * //     [d1, d2, d3, ...],
 * //     ...
 * //   ]
 * // }
 */
function computeORB3(imagePath, options) {
  if (typeof imagePath !== "string") throw new Error("File must be a string")
  if (options && typeof options !== "object")
    throw new Error("Params must be an object")

  options = Object.assign(
    {
      nFeatures: 1000,
      scaleFactor: 1.2,
      nLevels: 8,
      iniThFAST: 25,
      minThFAST: 6,
    },
    options
  )

  const paramsStr = `${options.nFeatures},${options.scaleFactor},${options.nLevels},${options.iniThFAST},${options.minThFAST}`
  let result = addon.computeORB3(path.resolve(imagePath), paramsStr).split("&")
  result = result.map((i) =>
    i.split(";").map((item) =>
      item
        .split(",")
        .filter((item) => item)
        .map((item) => parseFloat(item))
    )
  )
  result[0].pop()
  result[1].pop()

  return {
    descriptors: result[0],
    keypoints: result[1],
  }
}

module.exports = computeORB3
