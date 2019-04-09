; Auto-generated. Do not edit!


(cl:in-package gabor_runtime_monitoring-msg)


;//! \htmlinclude Average.msg.html

(cl:defclass <Average> (roslisp-msg-protocol:ros-message)
  ((average
    :reader average
    :initarg :average
    :type cl:float
    :initform 0.0))
)

(cl:defclass Average (<Average>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Average>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Average)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gabor_runtime_monitoring-msg:<Average> is deprecated: use gabor_runtime_monitoring-msg:Average instead.")))

(cl:ensure-generic-function 'average-val :lambda-list '(m))
(cl:defmethod average-val ((m <Average>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gabor_runtime_monitoring-msg:average-val is deprecated.  Use gabor_runtime_monitoring-msg:average instead.")
  (average m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Average>) ostream)
  "Serializes a message object of type '<Average>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'average))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Average>) istream)
  "Deserializes a message object of type '<Average>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'average) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Average>)))
  "Returns string type for a message object of type '<Average>"
  "gabor_runtime_monitoring/Average")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Average)))
  "Returns string type for a message object of type 'Average"
  "gabor_runtime_monitoring/Average")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Average>)))
  "Returns md5sum for a message object of type '<Average>"
  "711be0a796b85a8a1e109ae6a26ad085")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Average)))
  "Returns md5sum for a message object of type 'Average"
  "711be0a796b85a8a1e109ae6a26ad085")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Average>)))
  "Returns full string definition for message of type '<Average>"
  (cl:format cl:nil "float64 average~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Average)))
  "Returns full string definition for message of type 'Average"
  (cl:format cl:nil "float64 average~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Average>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Average>))
  "Converts a ROS message object to a list"
  (cl:list 'Average
    (cl:cons ':average (average msg))
))
