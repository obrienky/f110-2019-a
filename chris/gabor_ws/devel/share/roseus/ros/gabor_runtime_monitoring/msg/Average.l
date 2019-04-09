;; Auto-generated. Do not edit!


(when (boundp 'gabor_runtime_monitoring::Average)
  (if (not (find-package "GABOR_RUNTIME_MONITORING"))
    (make-package "GABOR_RUNTIME_MONITORING"))
  (shadow 'Average (find-package "GABOR_RUNTIME_MONITORING")))
(unless (find-package "GABOR_RUNTIME_MONITORING::AVERAGE")
  (make-package "GABOR_RUNTIME_MONITORING::AVERAGE"))

(in-package "ROS")
;;//! \htmlinclude Average.msg.html


(defclass gabor_runtime_monitoring::Average
  :super ros::object
  :slots (_average ))

(defmethod gabor_runtime_monitoring::Average
  (:init
   (&key
    ((:average __average) 0.0)
    )
   (send-super :init)
   (setq _average (float __average))
   self)
  (:average
   (&optional __average)
   (if __average (setq _average __average)) _average)
  (:serialization-length
   ()
   (+
    ;; float64 _average
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _average
       (sys::poke _average (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _average
     (setq _average (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get gabor_runtime_monitoring::Average :md5sum-) "711be0a796b85a8a1e109ae6a26ad085")
(setf (get gabor_runtime_monitoring::Average :datatype-) "gabor_runtime_monitoring/Average")
(setf (get gabor_runtime_monitoring::Average :definition-)
      "float64 average

")



(provide :gabor_runtime_monitoring/Average "711be0a796b85a8a1e109ae6a26ad085")


