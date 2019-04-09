
(cl:in-package :asdf)

(defsystem "gabor_runtime_monitoring-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Average" :depends-on ("_package_Average"))
    (:file "_package_Average" :depends-on ("_package"))
  ))