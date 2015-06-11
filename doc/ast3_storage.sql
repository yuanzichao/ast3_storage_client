/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50617
Source Host           : localhost:3306
Source Database       : ast3_storage

Target Server Type    : MYSQL
Target Server Version : 50617
File Encoding         : 65001

Date: 2015-04-24 14:41:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `directory_info`
-- ----------------------------
DROP TABLE IF EXISTS `directory_info`;
CREATE TABLE `directory_info` (
  `directory_id` int(11) NOT NULL AUTO_INCREMENT,
  `directory_name` varchar(255) NOT NULL,
  `disk_uuid` varchar(255) NOT NULL,
  `disk_name` varchar(255) NOT NULL,
  `parent_id` int(11) NOT NULL,
  `directory_size` double NOT NULL,
  `time` datetime NOT NULL,
  `recent_use_time` datetime NOT NULL,
  `permission` int(11) NOT NULL,
  `accessed_time` int(11) NOT NULL,
  `file_number` int(11) NOT NULL,
  PRIMARY KEY (`directory_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of directory_info
-- ----------------------------
INSERT INTO `directory_info` VALUES ('1', '20150424', '51bb74393f2646d7bd46b4427ade5e17', 'disk_001', '0', '1000', '2015-04-24 14:39:18', '2015-04-24 14:39:21', '0', '0', '2');
INSERT INTO `directory_info` VALUES ('2', '20150423', 'c839baea5e8b4513bf5ae156085d5d2d', 'disk_002', '0', '900', '2015-04-24 14:40:26', '2015-04-24 14:40:28', '0', '0', '1');

-- ----------------------------
-- Table structure for `disk_info`
-- ----------------------------
DROP TABLE IF EXISTS `disk_info`;
CREATE TABLE `disk_info` (
  `disk_id` int(11) NOT NULL AUTO_INCREMENT,
  `disk_name` varchar(255) NOT NULL,
  `disk_uuid` varchar(255) NOT NULL,
  `disk_type` varchar(255) NOT NULL,
  `disk_capacity` double NOT NULL,
  `disk_used` double NOT NULL,
  `recent_use_time` datetime NOT NULL,
  `permisssion` int(11) NOT NULL,
  `disk_status` int(11) NOT NULL,
  PRIMARY KEY (`disk_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of disk_info
-- ----------------------------
INSERT INTO `disk_info` VALUES ('1', 'disk_001', '51bb74393f2646d7bd46b4427ade5e17', 'ext3/ext4', '707.8', '500', '2015-04-24 14:37:11', '0', '0');
INSERT INTO `disk_info` VALUES ('2', 'disk_002', 'c839baea5e8b4513bf5ae156085d5d2d', 'ext3/ext4', '800', '300', '2015-04-24 14:38:24', '0', '0');

-- ----------------------------
-- Table structure for `file_info`
-- ----------------------------
DROP TABLE IF EXISTS `file_info`;
CREATE TABLE `file_info` (
  `file_id` int(11) NOT NULL AUTO_INCREMENT,
  `file_name` varchar(255) NOT NULL,
  `disk_uuid` varchar(255) NOT NULL,
  `directory_name` varchar(255) NOT NULL,
  `disk_name` varchar(255) NOT NULL,
  `md5` varchar(255) NOT NULL,
  `file_size` double NOT NULL,
  `ra_val` double NOT NULL,
  `dec_val` double NOT NULL,
  `time` datetime NOT NULL,
  `recent_use_time` datetime NOT NULL,
  `permission` int(11) NOT NULL,
  `file_type` int(11) NOT NULL,
  `accessed_time` int(11) NOT NULL,
  PRIMARY KEY (`file_id`)
)  ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of file_info
-- ----------------------------
INSERT INTO `file_info` VALUES ('1', '20150424_0001.fits', '51bb74393f2646d7bd46b4427ade5e17', '20150424', 'disk_001', '7F97854DC04C119D461FED14F5D8BB96', '100', '100.00', '100.00', '2015-04-24 14:31:17', '2015-04-24 14:31:24', '1', '1', '0');
INSERT INTO `file_info` VALUES ('2', '20150424_0002.fits', '51bb74393f2646d7bd46b4427ade5e17', '20150424', 'disk_001', '7F97854DC04C119D461FED14F5D8BB96', '200', '111.00', '111.00', '2015-04-24 14:33:37', '2015-04-24 14:33:40', '1', '1', '0');
INSERT INTO `file_info` VALUES ('3', '20150423_0001.fits', 'c839baea5e8b4513bf5ae156085d5d2d', '20150423', 'disk_002', '7F97854DC04C119D461FED14F5D8BB96', '150', '120.00', '120.00', '2015-04-24 14:35:53', '2015-04-24 14:35:56', '0', '0', '0');
